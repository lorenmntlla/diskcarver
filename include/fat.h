/**
 * @file fat.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/
#pragma once

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
  uint8_t jmp_boot[3];
  char oem_name[8];
  uint16_t bytes_per_sector;
  uint8_t sectors_per_cluster;
  uint16_t reserved_sectors_count;
  uint8_t number_of_FATs;
  uint16_t root_entry_counter;
  uint16_t total_sectors16;
  uint8_t media;
  uint16_t FAT_size16;
  uint16_t sectors_per_track;
  uint16_t number_of_heads;
  uint32_t hidden_sectors;
  uint32_t total_sectors32;
} FAT_common;

typedef struct {
  uint8_t drive_number;
  uint8_t reserved1;
  uint8_t boot_signature;
  uint32_t volume_id;
  char volume_label[11];
  char filesystem_type[8];
} FAT16;

typedef struct {
  uint32_t FAT_size32;
  uint16_t extra_flags;
  uint16_t filesystem_version;
  uint32_t root_cluster;
  uint16_t filesystem_info;
  uint16_t backup_boot_sector;
  uint8_t reserved[12];
  uint8_t drive_number;
  uint8_t reserved1;
  uint8_t boot_signature;
  uint32_t volume_id;
  char volume_label[11];
  char filesystem_type[8];
} FAT32;
#pragma pack(pop)
