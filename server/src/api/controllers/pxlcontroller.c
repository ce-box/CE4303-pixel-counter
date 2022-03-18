#include "pxlcontroller.h"

/**
 * @brief Receives an image and a pixel value (additive color model).
 * Returns the number of pixels in the image that are greater than the received pixel.
 *
 * @param req HTTP request.
 * @param res HTTP response.
 * @param user_data a pointer to a data or a structure that will be available in callback_function.
 * @return int U_CALLBACK_CONTINUE on success.
 */
int count_image_pixels(const struct _u_request *req, struct _u_response *res, void *user_data)
{
    const char *filename = u_map_get(req->map_post_body, "filename");
    const char *data = u_map_get(req->map_post_body, "file");
    const char *pixel_value = u_map_get(req->map_post_body, "npixel");

    int pxl = convert2int(pixel_value);

    // convert base64 to image and store it
    store_base64(data);
    decode_base64(filename);

    // count pixels
    int result = pixels_count(filename, pxl); // count_pixels(filename, pxl);

    printf("{ filename: %s, reference: %i, pixels: %i}\n", filename, pxl, result);

    char *res_body = malloc(sizeof(char) * 512);
    sprintf(res_body, "{ img: %s, reference: %i, pixels: %i }\n", filename, pxl, result);
    ulfius_set_string_body_response(res, 200, res_body);
    free(res_body);

    return U_CALLBACK_CONTINUE;
}