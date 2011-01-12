cmake_minimum_required (VERSION 2.6)
project (libgesture)

set (PROJECT_SOURCE_DIR .)

set (LIBGESTURE_VERSION_MAJOR 0)
set (LIBGESTURE_VERSION_MINOR 1)

configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (libgesture)
add_subdirectory (test_env)

