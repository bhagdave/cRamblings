#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <time.h>
#include <zlib.h>
#define BLOCKSIZE 1

struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;
size_t size;
uint8_t *fbp;
uint32_t block[BLOCKSIZE*BLOCKSIZE];
struct colour {
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
};

struct psf_header {
    uint8_t magic[2];
    uint8_t filemode;
    uint8_t fontheight;
};

struct psf2_header {
    unsigned char magic[4];
    unsigned int version;
    unsigned int headersize;
    unsigned int flags;
    unsigned int length;
    unsigned int charsize;
    unsigned int height, width;
};
struct psf2_header header;

void setPixel(uint32_t x,uint32_t y,uint32_t r,uint32_t g,uint32_t b,uint32_t a)
{
    uint32_t pixel = (r << vinfo.red.offset) | (g << vinfo.green.offset) | (b << vinfo.blue.offset) | (a << vinfo.transp.offset);
    uint32_t location = x*vinfo.bits_per_pixel/8 + y*finfo.line_length;
    *((uint32_t*) (fbp + location)) = pixel;
}


uint32_t getRawPixel(uint32_t x, uint32_t y) {
    uint32_t location = x * (vinfo.bits_per_pixel / 8) + y * finfo.line_length;
    return *((uint32_t*) (fbp + location));
}

uint32_t setRawPixel(uint32_t x, uint32_t y, uint32_t pixel) {
    uint32_t location = x * (vinfo.bits_per_pixel / 8) + y * finfo.line_length;
    *((uint32_t*) (fbp + location)) = pixel;
}


void setPixel2(uint32_t x,uint32_t y,struct colour c)
{
    uint32_t pixel = (c.r << vinfo.red.offset)| (c.g << vinfo.green.offset) | (c.b << vinfo.blue.offset) | (c.a << vinfo.transp.offset);
    setRawPixel(x, y, pixel);
}

void setBlock(uint32_t x, uint32_t y, uint32_t L, struct colour c)
{
    for (int i =0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            setPixel2(x + i, y + j,  c);
        }
    }
}

void saveBlock(uint32_t x, uint32_t y, uint32_t L, uint32_t block[])
{
    for (int i =0; i < L; i++) {
        for (int j =0; j < L; j++) {
            block[i+j*L] = getRawPixel(x + i, y + j);
        }
    }
}

void restoreBlock(uint32_t x, uint32_t y, uint32_t L, uint32_t block[])
{
    for (int i = 0; i < L ; i++){
        for (int j = 0; j < L; j++) {
            setRawPixel(x + i, y + j, block[i+j*L]);
        }
    } 
} 

void displayChar(char ch, int x, int y, struct colour c, uint8_t chars[])
{
    uint8_t row;
    int x1 = x;
    for (int i =0; i < 8; i++) {
        if (row & 0x80) {
            setBlock(x1, y, BLOCKSIZE, c);
        }
        row = row << 1;
        x1 = x1 + BLOCKSIZE;
    }
    y = y + BLOCKSIZE;
    x1 = x;
}
void displayCharPSF2(char ch, int x, int y, struct colour c, uint8_t chars[])
{
    uint8_t row;
    int x1 = x;
    int stride = header.charsize / header.height;
    int bits;
    for (int j =0; j < header.height; j++) {
        bits = 0;
        for (int i = 0; i < header.height; i++){
            row = chars[ch * header.charsize + i + j * stride];
            for (int b =0; b < 8; b++) {
                if (bits == header.width)
                    continue;
                if (row & 0x80) {
                    setBlock(x1 + bits*BLOCKSIZE, y, BLOCKSIZE, c);
                }
                row = row << 1;
                bits++;

            }
        }
        y = y + BLOCKSIZE;
        x1 = x;
    }
}

void displayString(char s[], int x, int y, struct colour c, uint8_t chars[]) {
    int k = 0;
    while (s[k]) {
        displayChar(s[k], x, y, c, chars);
        x = x + BLOCKSIZE * 9;
        k++;
    };
}

void displayStringPSF2(char s[], int x, int y, struct colour c, uint8_t chars[]) {
    int k = 0;
    while (s[k]) {
        displayCharPSF2(s[k], x, y, c, chars);
        x = x + BLOCKSIZE * header.width;
        k++;
    };
}
