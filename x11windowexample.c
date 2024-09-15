#include <stdio.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
  const char *text = "Hey, jean🥰";
  Display *display = XOpenDisplay(NULL);
  if(!display){
    fprintf(stderr, "ERROR: Couldn't Open diplay\n");
    exit(1);
  }
  int screen = DefaultScreen(display);
  Window rootWindow = XDefaultRootWindow(display);
  XWindowAttributes attributes;
  XGetWindowAttributes(display, rootWindow, &attributes);
  Window window = XCreateSimpleWindow(display, rootWindow, 0, 0,  600, 600, 0, 0, 0);
  XSelectInput(display, window, ExposureMask|KeyPressMask);
  XMapWindow(display, window);
  GC gc = DefaultGC(display, screen);
  XEvent event;
  XImage image;
  bool running = true;
  char *message = "Press `q` to quit the window.";
  while(running){
    XSetWindowBackground(display, window, 0x10050113);
    XNextEvent(display, &event);
    if(event.type == Expose){
      XSetForeground(display, gc, 0xff2233);
      XFillRectangle(display, window, gc, 10, 10, 100, 100);
      XSetForeground(display, gc, 0x14141414);
      XDrawString(display, window, gc, 20, 50, text, strlen(text));
      XSetForeground(display, gc, 0xEE1010);
      XDrawString(display, window, gc, 150, 150, message, strlen(message));
    }
    else if(event.type == KeyPress){
      KeySym key = XKeycodeToKeysym(display, event.xkey.keycode, 0);
      if(key == 'q'){
	running = false;
      }
    }
  }
  XCloseDisplay(display);
  return 0;
}
