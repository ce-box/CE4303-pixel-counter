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
    const char *data_b64 = u_map_get(req->map_post_body, "file");
    const char *pixel_value = u_map_get(req->map_post_body, "npixel");

    const char *data = decode(data_b64, sizeof(data_b64));
    int pxl = convert2int(pixel_value);

    printf("{ filename: %s, npixel: %i}\n", filename, pxl);

    save_image(filename, data);
    int result = count_pixels(filename, pxl);

    char *res_body = malloc(sizeof(char) * 512);
    sprintf(res_body, "{ img: %s, reference: %i, pixels: %i }\n", filename, pxl, result);
    ulfius_set_string_body_response(res, 200, res_body);
    free(res_body);

    return U_CALLBACK_CONTINUE;
}