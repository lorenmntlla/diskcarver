/**
 * @file disk.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/

#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

/**
 * Enum Permission for read-only, write-only and read-write disk opening
 * */
typedef enum { r = O_RDONLY, w = O_WRONLY, rw = O_RDWR } Permission;

/**
 * Struct Disk
 * */
typedef struct {
  int fd;
  size_t logical_sector_size;
  size_t physical_sector_size;
  size_t current_sector;
} Disk;

/**
 * Opens disk from file
 * @param path Path of disk
 * @param permission Desired disk access permission
 * @return Pointer to disk on the heap if successful, null pointer otherwise
 * */
Disk *disk_open(const char *path, Permission permission);

/**
 * Closes disk from disk pointer
 * @param disk Pointer to disk
 * @return Status
 * */
int disk_close(Disk *disk);

/**
 * Reads logical_sector_size bytes to specified buffer and advances current_sector
 * @param disk Pointer to Disk
 * @param buffer Buffer
 * @return Total of bytes read
 * */
ssize_t disk_read(Disk *disk, void *buffer);
