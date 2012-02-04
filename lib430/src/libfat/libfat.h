#ifndef __LIBFAT_H__
#define __LIBFAT_H__

int fs_fat_open(FAT_HANDLE* handle);

void fs_fat_close(FAT_HANDLE* handle);

void fs_fat_read_index();

#endif // __LIBFAT_H__
