#include "../include/disk.h"
#include <fcntl.h>
#include <linux/fs.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

Disk *disk_open(const char *path, const Permission permission) {
  Disk *disk = calloc(1, sizeof(Disk));

  disk->fd = open(path, (int)permission);
  if (disk->fd < 0) {
    perror("Failed to open file/disk");

    free(disk);
    return NULL;
  }

  struct stat st;
  if (fstat(disk->fd, &st) == -1) {

    free(disk);
    return NULL;
  }

  if (S_ISBLK(st.st_mode)) {
    disk->type = BLOCK_DEVICE;

    if (ioctl(disk->fd, BLKSSZGET, &disk->sector_size) < 0)
      disk->sector_size = 512;

    disk->current_sector = 0;

    if (ioctl(disk->fd, BLKGETSIZE64, &disk->total_bytes) < 0)
      disk->total_bytes = 0;

    return disk;
  }

  if (S_ISREG(st.st_mode)) {
    disk->type = IMAGE_FILE;
    disk->sector_size = 512;
    disk->total_bytes = (size_t)st.st_size;

    return disk;
  }

  free(disk);
  return NULL;
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

ssize_t disk_read(Disk *disk, void *buffer, ReadFlag advance) {
  const size_t next_chunk = (disk->current_sector + 1) * disk->sector_size;
  size_t bytes = disk->sector_size;

  if (next_chunk > disk->total_bytes) {
    ssize_t remaining = (ssize_t)disk->total_bytes -
                        ((ssize_t)next_chunk - (ssize_t)disk->sector_size);

    if (remaining <= 0)
      return -1;

    bytes = (size_t)remaining;
  }

  ssize_t retcode = read(disk->fd, buffer, bytes);

  if (retcode != (ssize_t)bytes)
    perror("Failed to read sector from disk");

  if (advance == NO_ADVANCE) {
    lseek(disk->fd, -(__off_t)bytes, SEEK_CUR);
    return retcode;
  }

  disk->current_sector++;

  return retcode;
}
