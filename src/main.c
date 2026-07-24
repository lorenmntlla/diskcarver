#include "../include/disk.h"
#include "../include/mbr.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <path_to_disk>\n", argv[0]);

    return EXIT_FAILURE;
  }

  Disk *disk = disk_open(argv[1], R);

  if (!disk)
    return EXIT_FAILURE;

  uint8_t *buffer = malloc(sizeof(*buffer) * disk->sector_size);

  ssize_t read = disk_read(disk, buffer, ADVANCE);
  if (read == -1)
    return EXIT_FAILURE;

  if (buffer[511] == 0xAA) {
    printf("Partition table is Master Boot Record\n");

    MBR_Entry part[4];

    memcpy(part, buffer + 446, 64);

    printf("partition type: %u", part[0].type);
  }

  free(buffer);
  disk_close(disk);

  return EXIT_SUCCESS;
}
