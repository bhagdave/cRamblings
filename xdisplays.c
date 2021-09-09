/*
 * Simple Xdisplay program to use x11
 *    Requires compiling with -lX11
 *
 * On AlmaLinux this requires install libX11-devel Library
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char** argv)
{
    Display *dpy = XOpenDisplay(None);
    int screen = DefaultScreen(dpy);

    int blackColor = BlackPixel(dpy, screen);
    int whiteColor = WhitePixel(dpy, screen);

    Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 200, 600, 500, 500, 0 , blackColor, blackColor);

    XMapWindow(dpy, w);
    XFlush(dpy);
    sleep(1);
    GC gc = XCreateGC(dpy, w, 0, 0);
    XSetForeground(dpy, gc, whiteColor);
    XDrawLine(dpy, w, gc, 10, 10, 200, 20);
    XDrawRectangle(dpy, w, gc, 30, 200, 100, 200);
    XDrawRectangle(dpy, w, gc, 200, 200, 100, 200);
    XDrawString(dpy, w, gc, 35, 300, "Hello X world", 13);
    XFlush(dpy);
    sleep(10);
    return (EXIT_SUCCESS);
}
