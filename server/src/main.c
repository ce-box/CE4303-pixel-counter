#include "./logging/logging.h"
#include "./config/config.h"
#include "./api/server.h"
#include "./images/pixels.h"

int main(int argc, char const *argv[])
{

    Config *config = get_configuration();
    printf("{port: %i, logger: %s, gallery: %s}\n", config->port, config->logger, config->gallery);

    set_logging_path(config->logger);
    set_gallery_path(config->gallery);
    run(config->port);

    return 0;
}
