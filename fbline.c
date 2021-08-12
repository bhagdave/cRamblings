#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <inttypes.h>

struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;
size_t size;
uint8_t *fbp;

void setPixel(uint32_t x,uint32_t y,uint32_t r,uint32_t g,uint32_t b,uint32_t a)
{
    uint32_t pixel = (r << vinfo.red.offset) | (g << vinfo.green.offset) | (b << vinfo.blue.offset) | (a << vinfo.transp.offset);
    uint32_t location = x*vinfo.bits_per_pixel/8 + y*finfo.line_length;
    *((uint32_t*) (fbp + location)) = pixel;
}

int main(int argc, char** argv) 
{
    int fd =open("/dev/fb0", O_RDWR); //open up the framebuffer

    // get the fb details
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);

    // calculate the size
    size = vinfo.yres * finfo.line_length;
    // wack into memory
    fbp = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    uint32_t x = 0;
    uint32_t y = 400;
    for(x = 0; x < vinfo.xres; x++) {
        setPixel(x , y, 0xFF, 0xFF, 0x00, 0xFF);
    } 

    for(y = 0, x = 0; x < vinfo.xres, y < vinfo.yres; y++, x++) {
        setPixel(x , y, 0xFF, 0x00, 0x00, 0x00);
    } 
    return (EXIT_SUCCESS);
}
