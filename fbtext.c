/*
 * Must be compiled with -lz to include the zlib
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include "fbGraphics.h"


int main(int argc, char** argv) 
{
    int fd =open("/dev/fb0", O_RDWR); //open up the framebuffer
    if (! fd){
        fprintf(stderr, "Unable to open frame buffer");
        exit(EXIT_FAILURE);
    }

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
    int x = 50;
    int y = 400;
    size_t length;


    gzFile font = gzopen("/usr/lib/kbd/consolefonts/lat9-16.psf.gz","r");
    if (font == NULL){
        fprintf(stderr, "Unable to open font file\n");
        exit(EXIT_FAILURE);
    }
    gzread(font, &header, sizeof(header));
    printf("Version %d, Characters %d, Char Size %d\n", header.version, header.length, header.charsize);

    uint8_t chars[header.height * header.length];
    length = gzread(font, chars, header.height * header.length);
    if (length < 0) {
        fprintf(stderr, "Unable to read in font\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Read in %d chars\n", length);
    }

    displayStringPSF2("Hello World!", x, y,c, chars);

    return (EXIT_SUCCESS);
}


