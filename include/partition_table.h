/**
 * @file partition_table.h
 * @author Loren Montilla
 *
 * @license SPDX-License-Identifier: GPL-3.0+ (see COPYING)
 **/
#pragma once

#include "../include/disk.h"

typedef enum { INVALID = 0, MASTER_BOOT_RECORD, GUID } PartitionTable;

PartitionTable get_PartitionTable(Disk *disk);
