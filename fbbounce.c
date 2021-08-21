#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <time.h>
#define BLOCKSIZE 50

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

int main(int argc, char** argv) 
{
    int fd =open("/dev/fb0", O_RDWR); //open up the framebuffer

    // get the fb details
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    vinfo.grayscale = 0;
    vinfo.bits_per_pixel = 32;
    ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo);
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);

    // calculate the size
    size = vinfo.yres * finfo.line_length;
    // wack into memory
    fbp = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    struct colour c = {0xFF, 0x0F, 0xAC, 0x0F};
    int x = 600;
    int y = 400;
    int vx = -2;
    int vy = -2;
    struct timespec pause;
    pause.tv_sec = 0;
    pause.tv_nsec = 10 * 1000*1000;

    saveBlock(x, y, BLOCKSIZE, block);
    for(;;) {

        //ioctl(fd, FBIO_WAITFORVSYNC, 0);
        restoreBlock(x, y, BLOCKSIZE, block);
        x = x + vx;
        y = y + vy;
        if (x <= 0 ){
            x = 0; vx = -vx;
        }
        if (y <= 0) {
            y = 0; vy = -vy;
        }
        if ((x + BLOCKSIZE) >= vinfo.xres) {
            x = vinfo.xres - BLOCKSIZE - 1;
            vx = -vx;
        }
        if ((y + BLOCKSIZE) >= vinfo.yres) {
            y = vinfo.yres - BLOCKSIZE - 1;
            vy = -vy;
        }
        saveBlock(x, y, BLOCKSIZE, block);
        setBlock(x, y, BLOCKSIZE, c);
        nanosleep(&pause, NULL);
        
    }


    return (EXIT_SUCCESS);
}
