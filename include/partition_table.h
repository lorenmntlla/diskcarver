/**
 * @file partition_table.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/
#pragma once

#include "../include/disk.h"

/**
 * Enum PartitionTable denoting supported partition tables
 * */
typedef enum { INVALID = 0, MASTER_BOOT_RECORD, GUID } PartitionTable;

/**
 * Get partition table from disk
 * @param disk Pointer to disk
 * @return Partition table
 * */
PartitionTable get_PartitionTable(Disk *disk);
