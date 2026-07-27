/**
 * @file mbr.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/
#pragma once

#include "../include/disk.h"
#include <stdint.h>

/**
 * Struct for Master Boot Record Entry
 * */
#pragma pack(push, 1)
typedef struct {
  uint8_t status;
  uint8_t chs_start[3];
  uint8_t type;
  uint8_t chs_end[3];
  uint32_t lba_start;
  uint32_t num_sectors;
} MBR_Entry;
#pragma pack(pop)

/**
 * Get Master Boot Record entries (partitions) from a MBR formatted disk
 * @param disk Pointer to disk
 * @return Pointer to MBR entries in heap
 * */
MBR_Entry *get_MBR_entries(Disk *disk);
