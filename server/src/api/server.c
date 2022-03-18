#include "server.h"

/**
 * @brief Allows Cross-Origin Resource Sharing (CORS).
 *
 * @param req HTTP request.
 * @param res HTTP response.
 * @param user_data a pointer to a data or a structure that will be available in callback_function.
 * @return int U_CALLBACK_COMPLETE on success.
 */
int allow_cors(const struct _u_request *req, struct _u_response *res, void *user_data)
{
    u_map_put(res->map_header, "Access-Control-Allow-Origin", "*");
    u_map_put(res->map_header, "Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    u_map_put(res->map_header, "Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept, Bearer, Authorization");
    u_map_put(res->map_header, "Access-Control-Max-Age", "1800");
    return U_CALLBACK_COMPLETE;
}

/**
 * @brief Deploy server and listen on specified port.
 *
 * @param port Port the server will listen on.
 * @return int Returns zero if the server ran and terminated successfully. If an error occurs, return -1.
 */
int run(int port)
{
    struct _u_instance instance;

    if (ulfius_init_instance(&instance, port, NULL, NULL))
    {
        fprintf(stderr, "[Error] Could not initialize ulfius server instance ...\n");
        exit(-1);
    }

    ulfius_add_endpoint_by_val(&instance, "OPTIONS", NULL, "*", 0, &allow_cors, NULL);
    ulfius_add_endpoint_by_val(&instance, "POST", "/image_server/pixels", NULL, 0, &count_image_pixels, NULL);

    if (ulfius_start_framework(&instance) == U_OK)
    {
        char msg[32];
        sprintf(msg, "Server running on port: %d", port);
        printf("%s...\n", msg);
        logging(msg);
        while (1)
            ; // infite loop
    }
    else
    {
        fprintf(stderr, "[Error] Failure starting framework ...\n");
        logging("[Error] Failure starting framework");
        exit(-1);
    }

    printf("Terminating framework ...\n");
    logging("Terminating framework");

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    printf("Server shutdown successfully ...\n");
    logging("Server shutdown successfully");

    return 0;
}