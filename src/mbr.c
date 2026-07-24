#include "../include/mbr.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

MBR_Entry *get_MBR_Entries(Disk *disk) {
  MBR_Entry *entries = calloc(4, sizeof(*entries));

  uint8_t header[512];
  disk_read(disk, header, NO_ADVANCE);

  memcpy(entries, header + 446, 64);

  return entries;
}
