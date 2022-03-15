#include "config.h"

Config *get_configuration()
{

    FILE *fptr = fopen("/home/estalvgs/Documentos/tec/sistemas-operativos/CE4303-pixel-counter/server/server.config", "r");
    int line_size = 128;
    char *line = malloc(sizeof(char) * line_size);

    if (fptr == NULL)
    {
        fprintf(stderr, "[Error] Unable to open config file ...\n");
        exit(EXIT_FAILURE);
    }

    char **config_values = malloc(sizeof(char *) * 3);
    int c = 0;

    while (fgets(line, line_size, fptr) > 0)
    {
        char *split = strdup(line);
        char **values = malloc(sizeof(char *) * 2);
        for (int i = 0; i < 2; i++)
            values[i] = strsep(&split, ":");
        config_values[c] = values[1];
        strtok(config_values[c], "\n");
        free(values);
        free(split);
        c++;
    }

    Config *config = malloc(sizeof(Config));
    config->port = atoi(config_values[0]);
    config->logger = config_values[1];
    config->gallery = config_values[2];

    free(config_values);
    return config;
}