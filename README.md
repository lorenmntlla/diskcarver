# DiskCarver
DiskCarver is a low-level command-line utility written in C for interfacing with block devices and raw disk images on Linux. It utilizes POSIX system calls to read storage media sector-by-sector and outputs the binary data as a formatted hex dump (for now)

## Prerequisites
- Linux (Requires `<linux/fs.h>` and POSIX headers)
- CMake 3.31 or higher
- C Compiler with C17 standard support

## Building
```shell
cmake -B build
cmake --build build
```

## Usage
Run the compiled executable by passing the target path and the number of sectors you want to read

```shell
$ ./diskcarver <path_to_disk> <number_of_sectors>
```

Example 1: Reading a raw disk image

```shell
$ ./diskcarver pendrive.img 10
```

Example 2: Reading a physical block device _(Note: Acessing devices in `/dev/` usually requires root privileges)_

```shell
# ./diskcarver /dev/sda 5 
```
