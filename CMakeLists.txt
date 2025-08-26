cmake_minimum_required(VERSION 3.10)

project(sslb-libs)

set (SRC_FILES src/Logging.c src/main.c)

add_executable(sslb-lib-test ${SRC_FILES})


