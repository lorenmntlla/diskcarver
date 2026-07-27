#include "../include/disk.h"
#include "../include/mbr.h"
#include "../include/partition_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <path_to_disk>\n", argv[0]);

    return EXIT_FAILURE;
  }

  Disk *disk = disk_open(argv[1], R);

  if (!disk)
    return EXIT_FAILURE;

  switch (get_PartitionTable(disk)) {
  case INVALID: {
    puts("Disk does not contain a supported partition table");
    break;
  }
  case MASTER_BOOT_RECORD: {
    puts("Partition table is Master Boot Record");
    MBR_Entry *part = get_MBR_entries(disk);

    for (size_t i = 0; i < 4; i++) {
      printf("partition %lu:\n", i + 1);
      printf("\tstatus: %#2.2x\n", part[i].status);
      printf("\ttype: %#2.2x\n", part[i].type);
      printf("\tLBA of first sector: %u\n", part[i].lba_start);
      printf("\tNumber of sectors: %u\n", part[i].num_sectors);
    }

    free(part);
    break;
  }
  case GUID: {
    puts("Partition table is GUID");
  } break;
  }

  disk_close(disk);

  return EXIT_SUCCESS;
}
