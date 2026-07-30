#include "../include/mbr.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

MBR_Entry *get_MBR_entries(Disk *disk) {
  MBR_Entry *entries = calloc(4, sizeof(*entries));

  uint8_t *header = calloc(1, disk->sector_size);

  off_t previous_offset = disk_seek(disk, 0, SEEK_CUR);

  disk_seek(disk, 0, SEEK_SET);
  ssize_t read = disk_read(disk, header);

  if (read < 512) {
    free(entries);
    disk_seek(disk, previous_offset, SEEK_SET);

    return NULL;
  }

  memcpy(entries, header + 0x01BE, 64);

  free(header);
  disk_seek(disk, previous_offset, SEEK_SET);

  return entries;
}
