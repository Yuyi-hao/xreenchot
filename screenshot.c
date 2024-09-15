#include <stdio.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void saveToFile(const char *filePath, XImage *image){
  FILE *imageFile = fopen(filePath, "wb");
  fprintf(imageFile, "P6\n%zu %zu 255\n", image->width, image->height);
  for(int i=0; i < image->width*image->height; i++){
    uint8_t bytes[3] = {
      image->data[i*4+2],
      image->data[i*4+1],
      image->data[i*4+0]
    };
    fwrite(bytes, sizeof(bytes), 1, imageFile);
  }
  fclose(imageFile);
  return;
}

void displayImage(XImage *image){
  
}

int main(){
  Display *display = XOpenDisplay(NULL);
  Window rootWindow = XDefaultRootWindow(display);
  XWindowAttributes attributes;
  XGetWindowAttributes(display, rootWindow, &attributes); 
  Window window = XCreateSimpleWindow(display, rootWindow, 0, 0,  attributes.width, attributes.height, 0, 0, 0);
  XImage *image = XGetImage(display, rootWindow, 0, 0, attributes.width, attributes.height, AllPlanes, ZPixmap);
  printf("%d %d\n", image->width, image->height);
  saveToFile("image.ppm", image);
  displayImage(image);
  return 0;
}
