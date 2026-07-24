/**
 * @file mbr.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/
#pragma once

#include "../include/disk.h"
#include <stdint.h>

#pragma pack(push, 1)
/**
 * Master Boot Record Entry
 * */
typedef struct {
  uint8_t status;
  uint8_t chs_start[3];
  uint8_t type;
  uint8_t chs_end[3];
  uint32_t lba_start;
  uint32_t num_sectors;
} MBR_Entry;
#pragma pack(pop)

MBR_Entry *get_MBR_Entries(Disk *disk);
