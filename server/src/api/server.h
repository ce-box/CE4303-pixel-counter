#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <ulfius.h>
#include "../logging/logging.h"
#include "./controllers/pxlcontroller.h"

int allow_cors(const struct _u_request *req, struct _u_response *res, void *user_data);
int run(int port);

#endif