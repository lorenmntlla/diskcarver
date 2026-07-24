#include "../include/disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 3)
    return EXIT_FAILURE;

  Disk *disk = disk_open(argv[1], R);

  if (!disk)
    return EXIT_FAILURE;

  size_t sectors = (size_t)atoi(argv[2]);

  size_t j = 0;

  char buffer[disk->logical_sector_size];

  while (sectors > disk->current_sector) {
    disk_read(disk, buffer);

    for (size_t i = 0; i < disk->logical_sector_size; i++, j++) {
      if (j % 16 == 0) {
        if (j != 0)
          printf("\n");

        printf("%7.7lx ", j);
      }

      if (i % 8 == 0)
        printf(" ");

      printf("%2.2x ", buffer[i] & 0xff);
    }
  }
  printf("\n");

  disk_close(disk);

  return EXIT_SUCCESS;
}
