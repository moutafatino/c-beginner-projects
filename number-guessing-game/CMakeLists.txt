cmake_minimum_required(VERSION 3.5.0)

set(VERSION "0.0.1")
set(PROJECT_NAME "c-project-starter")

project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES C)

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(
${PROJECT_NAME}
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE
-pedantic-errors
-Wall
-Wextra
-Wconversion
-Wsign-conversion
-Werror
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
enable_testing()
