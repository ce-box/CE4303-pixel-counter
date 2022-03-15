#ifndef PIXELS_H_
#define PIXELS_H_

//#include <MagicWand/MagickWand.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include <unistd.h>

char *gallery_path;

void set_gallery_path(char *path);
int count_pixels(const char *filename, int reference_value);
void save_image(const char *filename, const char *data);

#endif