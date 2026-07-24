#include "../include/partition_table.h"
#include <stdint.h>

PartitionTable get_PartitionTable(Disk *disk) {
  uint8_t header[512];

  disk_read(disk, header, NO_ADVANCE);

  if (header[510] == 0x55 && header[511] == 0xAAll)
    return MASTER_BOOT_RECORD;

  //TODO: check for GUID Partition Table

  return INVALID;
}
