#ifndef PXLCONTROLLER_H_
#define PXLCONTROLLER_H_

#include <ulfius.h>
#include "../../images/pixels.h"
#include "../../utils/convert2int.h"
#include "../../logging/logging.h"

int count_image_pixels(const struct _u_request *req, struct _u_response *res, void *user_data);

#endif