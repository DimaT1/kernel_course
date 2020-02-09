# Simple filesystem.

Written using libc.

The filesystem consists of:
  - superblock (48 bytes)
    - 8 bytes to encode blocks count
    - 8 bytes to encode inodes count
    - 8 bytes to encode free blocks amount
    - 8 bytes to encode free inodes amount
    - 8 bytes to encode block size (block size should be from 512 to 4096 (bytes))
    - 8 bytes to encode inode size (inode size should be from 1 to 4 (blocks))
  - blocks usage table
    - (block count bits rounded to the minimal bytes amount to encode them) to encode each block being used or not
  - inodes usage table (inodes count * inode size * block size)
    - (inodes count) of inodes
  - blocks

Block consists of:
  - 8 bytes length of used space
  - data bytes

Inode consists of:
  - 8 bytes id
  - 8 bytes file size in bytes
  - 8 bytes references count
  - 1 byte bool (is a link or not)
  - 1 byte bool (is a directory or not)
  - child nodes ids (only one if this inode is a link)
