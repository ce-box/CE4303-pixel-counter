#include "pixels.h"

void set_gallery_path(char *path)
{
    gallery_path = path;
}

int count_pixels(const char *filename, int reference_value)
{
    return 10;
}

void save_image(const char *filename, const char *data)
{
    char *path = (char *)malloc(1 + strlen(gallery_path) + strlen(filename));

    // strcpy(path, gallery_path); // server/img
    // strcat(path, filename);     // server/img/image.png
    sprintf(path, "%s/%s", gallery_path, filename);

    FILE *fptr = fopen(path, "w+");

    free(path);

    if (fptr == NULL)
    {
        fprintf(stderr, "[Error] Not found directory, creating...");
        mkdir(gallery_path, 0700);
        FILE *fptr = fopen(path, "w+");
        if (fptr == NULL)
        {
            perror("fopen()");
            return;
        }
    }

    printf("Created file on %s: %s\n", filename, path);
    fwrite(data, 1, strlen(data), fptr);
    fclose(fptr);
}