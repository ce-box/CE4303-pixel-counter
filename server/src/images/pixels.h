#ifndef PIXELS_H_
#define PIXELS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE 100

char *gallery_path;

struct RGB
{
    int r, g, b;
    int last;
};

void set_gallery_path(char *path);
void store_base64(const char *data);
void decode_base64(const char *filename);
void decode(FILE *encoded, FILE *decoded);
int count_pixels(const char *filename, int reference_value);

#endif