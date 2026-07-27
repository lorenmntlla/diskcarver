#include "../include/partition_table.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

PartitionTable get_PartitionTable(Disk *disk) {
  uint8_t *header = calloc(1, disk->sector_size);

  disk_read(disk, header);

  if (header[0x1FE] != 0x55 || header[0x1FF] != 0xAA) {
    free(header);
    disk_seek(disk, 0, SEEK_SET);

    return INVALID;
  }

  if (disk->sector_size < 1024)
    disk_read(disk, header);

  disk_seek(disk, 0, SEEK_SET);

  if (strncmp((char *)header, "EFI PART", 8) == 0) {
    free(header);

    return GUID;
  }

  free(header);

  return MASTER_BOOT_RECORD;
}
