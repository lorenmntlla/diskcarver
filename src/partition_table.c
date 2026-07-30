#include "../include/partition_table.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

PartitionTable get_PartitionTable(Disk *disk) {
  uint8_t *header = calloc(1, disk->sector_size);

  disk_seek(disk, 0, SEEK_SET);
  disk_read(disk, header);

  if (header[0x1FE] != 0x55 || header[0x1FF] != 0xAA) {
    free(header);
    disk_seek(disk, 0, SEEK_SET);

    return INVALID;
  }

  // Read LBA 1 into buffer
  disk_read(disk, header);

  if (strncmp((char *)header, "EFI PART", 8) == 0) {
    free(header);
    disk_seek(disk, 0, SEEK_SET);

    return GUID;
  }

  free(header);
  disk_seek(disk, 0, SEEK_SET);

  return MASTER_BOOT_RECORD;
}
