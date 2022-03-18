#include "pixels.h"
#include <b64/cdecode.h>

/**
 * @brief Set the gallery path object
 *
 * @param path
 */
void set_gallery_path(char *path)
{
    char *root = getenv("CROOT");
    gallery_path = malloc(sizeof(char) * 512);
    sprintf(gallery_path, "%s%s", root, path);
}

/**
 * @brief
 *
 * @param filename
 * @param reference_value
 * @return int
 */
int count_pixels(const char *filename, int reference_value)
{
    logging("Counting pixels");

    // Execute subroutine for image analysis
    char *root = getenv("CROOT");
    char *command = malloc(sizeof(char) * 1024);
    sprintf(command, "python3 %s/src/images/pixel_counter.py %s %i", root, filename, reference_value);
    system(command);

    free(command);

    // Read result value
    char *path = malloc(sizeof(char) * 512);
    sprintf(path, "%s/tmp/result.txt", gallery_path);

    FILE *fptr;
    fptr = fopen(path, "r");

    char *buffer = malloc(sizeof(char) * 16);
    fread(buffer, sizeof(char), 16, fptr);
    fclose(fptr);
    free(path);

    return atoi(buffer);
}

/**
 * @brief
 *
 * @param data
 */
void store_base64(const char *data)
{
    FILE *encoded_file;
    char *path = malloc(sizeof(char) * 512);
    sprintf(path, "%s/tmp/buffer.txt", gallery_path);
    encoded_file = fopen(path, "w+");
    fprintf(encoded_file, data);
    fclose(encoded_file);
}

/**
 * @brief
 *
 * @param filename
 */
void decode_base64(const char *filename)
{
    FILE *encoded_file, *img;

    char *img_path = malloc(sizeof(char) * 512);
    sprintf(img_path, "%s/%s", gallery_path, filename);

    char *buffer_path = malloc(sizeof(char) * 512);
    sprintf(buffer_path, "%s/tmp/buffer.txt", gallery_path);

    encoded_file = fopen(buffer_path, "r");
    img = fopen(img_path, "w+");

    decode(encoded_file, img);

    fclose(encoded_file);
    fclose(img);

    // clear temporary buffer
    encoded_file = fopen(buffer_path, "w");
    fclose(encoded_file);

    // free pointers
    free(buffer_path);
    free(img_path);
}

/**
 * @brief
 *
 * @param inputFile
 * @param outputFile
 */
void decode(FILE *inputFile, FILE *outputFile)
{
    /* set up a destination buffer large enough to hold the decoded data */
    int size = SIZE;
    char *encoded = (char *)malloc(size);
    char *decoded = (char *)malloc(1 * size); /* ~3/4 x encoded */
    /* we need an encoder and decoder state */
    base64_decodestate ds;
    /* store the number of bytes encoded by a single call */
    int cnt = 0;

    /*---------- START DECODING ----------*/
    /* initialise the encoder state */
    base64_init_decodestate(&ds);
    /* gather data from the input and send it to the output */
    while (1)
    {
        cnt = fread(encoded, sizeof(char), size, inputFile);
        if (cnt == 0)
            break;
        cnt = base64_decode_block(encoded, cnt, decoded, &ds);
        /* output the encoded bytes to the output file */
        fwrite(decoded, sizeof(char), cnt, outputFile);
    }
    /*---------- START DECODING  ----------*/

    free(encoded);
    free(decoded);
}
