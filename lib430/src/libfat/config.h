#ifndef __LIBFAT_CONFIG_H__
#define __LIBFAT_CONFIG_H__

#ifndef LIBFAT_ENABLE_FAT12
#define LIBFAT_ENABLE_FAT12 1
#endif
#ifndef LIBFAT_ENABLE_FAT32
#define LIBFAT_ENABLE_FAT32 0
#endif
#ifndef LIBFAT_WITH_LSEEK
#define LIBFAT_WITH_LSEEK 0
#endif
#ifndef LIBFAT_WITH_READ
#define LIBFAT_WITH_READ 1
#endif
#ifndef LIBFAT_WITH_READDIR
#define LIBFAT_WITH_READDIR 0
#endif
#ifndef LIBFAT_WITH_WRITE
#define LIBFAT_WITH_WRITE 0
#endif

// LIBFAT_WITH_READ: 1
#define	_USE_READ	LIBFAT_WITH_READ /* 1:Enable pf_read() */
// LIBFAT_WITH_READDIR: 0
#define	_USE_DIR	LIBFAT_WITH_READDIR /* 1:Enable pf_opendir() and pf_readdir() */
// LIBFAT_WITH_LSEEK: 0
#define	_USE_LSEEK	LIBFAT_WITH_LSEEK /* 1:Enable pf_lseek() */
// LIBFAT_WITH_WRITE: 0
#define	_USE_WRITE  LIBFAT_WITH_WRITE /* 1:Enable pf_write() */

// LIBFAT_ENABLE_FAT12: 1
#define _FS_FAT12	LIBFAT_ENABLE_FAT12 /* 1:Enable FAT12 support */
// LIBFAT_ENABLE_FAT32: 0
#define _FS_FAT32	LIBFAT_ENABLE_FAT32 /* 1:Enable FAT32 support */

#endif

