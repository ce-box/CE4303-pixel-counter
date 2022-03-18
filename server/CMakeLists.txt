cmake_minimum_required(VERSION 3.16.3)
project(ImageServer VERSION 0.1.0)

add_executable(
    ImageServer
    src/main.c
    src/api/server.c
    src/api/controllers/pxlcontroller.c
    src/images/pixels.c
    src/config/config.c
    src/logging/logging.c
    src/utils/convert2int.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(${PROJECT_NAME} ulfius)
target_link_libraries(${PROJECT_NAME} b64)