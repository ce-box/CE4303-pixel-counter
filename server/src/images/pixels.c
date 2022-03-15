#include "pixels.h"
#include <b64/cdecode.h>

void set_gallery_path(char *path)
{
    gallery_path = path;
}

int count_pixels(const char *filename, int reference_value)
{
    int result, size;

    char *img_path = malloc(sizeof(char) * 512);
    sprintf(img_path, "%s/%s", gallery_path, filename);

    FILE *input_file = fopen(img_path, "rb");
    fseek(input_file, 0, SEEK_END);
    size = ftell(input_file);
    rewind(input_file);

    char *data = malloc(size * sizeof(char));
    fread(data, sizeof(char), size, input_file);

    fclose(input_file);

    for (int i = 0; i < size; i += 3)
    {
        int avg_pxl = 0;

        for (int j = 0; j < 3; j++)
        {
            const char *pxl = &data[i + j];
            avg_pxl += atoi(pxl);
        }

        if (avg_pxl > reference_value)
            result++;
    }

    return result;
}

void store_base64(const char *data)
{
    FILE *encoded_file;
    char *path = malloc(sizeof(char) * 512);
    sprintf(path, "%s/tmp/buffer.txt", gallery_path);
    encoded_file = fopen(path, "w+");
    fprintf(encoded_file, data);
    fclose(encoded_file);
}

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
