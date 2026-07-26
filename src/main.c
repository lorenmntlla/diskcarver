#include "../include/disk.h"
#include "../include/mbr.h"
#include "../include/partition_table.h"
#include <stdint.h>
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

  if (get_PartitionTable(disk) == MASTER_BOOT_RECORD) {
    MBR_Entry *partitions = get_MBR_Entries(disk);

    for (size_t i = 0; i < 4; i++) {
      printf("partition %lu status: %#x\n", i, partitions[i].status);
    }

    free(partitions);
  } else
    printf("Partition table is not MBR\n");

  disk_close(disk);

  return EXIT_SUCCESS;
}
