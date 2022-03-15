#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char *log_file;

void set_logging_path(char *log_path);
void logging(char *msg);
char *time_stamp();

#endif