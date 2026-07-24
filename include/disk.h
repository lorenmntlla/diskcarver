/**
 * @file disk.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/
#pragma once

#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

/**
 * Enum Permission for read-only, write-only and read-write disk opening
 * */
typedef enum { R = O_RDONLY, W = O_WRONLY, RW = O_RDWR } Permission;

/**
 * Enum DiskType describing if it is a physical block device
 * */
typedef enum { BLOCK_DEVICE = 0, IMAGE_FILE } DiskType;

/**
 * Struct Disk
 * */
typedef struct {
  int fd;
  DiskType type;
  size_t sector_size;
  size_t current_sector;
  size_t total_bytes;
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
 * Reads sector_size bytes to specified buffer and advances current_sector
 * if not EOF
 * @param disk Pointer to Disk
 * @param buffer Buffer
 * @return Total of bytes read
 * */
ssize_t disk_read(Disk *disk, void *buffer);
