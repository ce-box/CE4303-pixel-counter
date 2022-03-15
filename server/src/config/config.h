#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// const char *root_dir = "/home/estalvgs/Documentos/tec/sistemas-operativos/CE4303-pixel-counter/server";

typedef struct
{
    int port;
    char *gallery;
    char *logger;
} Config;

Config *get_configuration();

#endif