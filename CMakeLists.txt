cmake_minimum_required(VERSION 3.31...4.4)

project(diskcarver VERSION 0.1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(APP_NAME "diskcarver")

set(COMPILE_OPTIONS "-pipe" "-Wall" "-Wextra" "-Wabi" "-Wconversion" "-pedantic" "-Wfatal-errors")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED YES)

add_library(disk src/disk.c include/disk.h)
target_compile_options(disk PRIVATE ${COMPILE_OPTIONS})

add_library(mbr src/mbr.c include/mbr.h)
target_compile_options(mbr PRIVATE ${COMPILE_OPTIONS})

add_executable(${APP_NAME} src/main.c)
target_include_directories(${APP_NAME} PRIVATE include)
target_link_libraries(${APP_NAME} PRIVATE disk mbr)
target_compile_options(${APP_NAME} PRIVATE ${COMPILE_OPTIONS})
