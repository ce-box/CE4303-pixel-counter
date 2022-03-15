#ifndef BYTE_ARRAY_H_
#define BYTE_ARRAY_H_

#include <b64/cencode.h>
#include <b64/cdecode.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* arbitrary buffer size */
#define SIZE 100

char *encode(const char *input, int size);
char *decode(const char *input, int size);

#endif