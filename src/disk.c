#include "../include/disk.h"
#include <fcntl.h>
#include <linux/fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

Disk *disk_open(const char *path, const Permission permission) {
  Disk *disk = malloc(sizeof(Disk));

  disk->fd = open(path, (int)permission);

  if (ioctl(disk->fd, BLKSSZGET, &disk->logical_sector_size) < 0) {
    perror("Failed to get logical sector size");

    free(disk);
    return NULL;
  }

  if (ioctl(disk->fd, BLKPBSZGET, &disk->physical_sector_size) < 0) {
    perror("Failed to get physical sector size");

    free(disk);
    return NULL;
  }

  disk->current_sector = 0;

  return disk;
}

int disk_close(Disk *disk) {
  int retcode = 0;

  if (close(disk->fd) == -1) {
    perror("Failed to close disk");
    retcode = -1;
  }

  free(disk);

  return retcode;
}

ssize_t disk_read(Disk *disk, void *buffer) {
  ssize_t retcode = read(disk->fd, buffer, disk->logical_sector_size);

  if (retcode != (ssize_t)disk->logical_sector_size)
    perror("Failed to read sector from disk");

  disk->current_sector++;

  return retcode;
}
