#include <sys/types.h>
       #include <sys/stat.h>
       #include <stdint.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       //#include <sys/sysmacros.h>

       int
       main(int argc, char *argv[])
       {
           struct stat sb;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
           }

           printf("ID of containing device:  [%jx,%jx]\n",
                   (uintmax_t) major(sb.st_dev),
                   (uintmax_t) minor(sb.st_dev));

           printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ju\n", (uintmax_t) sb.st_ino);

           printf("Mode:                     %jo s  (octal)\n",
                   (uintmax_t) sb.st_mode);

           printf("Link count:               %ju\n", (uintmax_t) sb.st_nlink);
           printf("Ownership:                UID=%ju   GID=%ju\n",
                   (uintmax_t) sb.st_uid, (uintmax_t) sb.st_gid);

           printf("Preferred I/O block size: %jd bytes\n",
                   (intmax_t) sb.st_blksize);
           printf("File size:                %jd bytes\n",
                   (intmax_t) sb.st_size);
           printf("Blocks allocated:         %jd\n",
                   (intmax_t) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));

           exit(EXIT_SUCCESS);
       }

/*struct stat {
               dev_t     st_dev;         /* ID of device containing file 
               ino_t     st_ino;         /* Inode number 
               mode_t    st_mode;        /* File type and mode 
               nlink_t   st_nlink;       /* Number of hard links 
               uid_t     st_uid;         /* User ID of owner 
               gid_t     st_gid;         /* Group ID of owner 
               dev_t     st_rdev;        /* Device ID (if special file) 
               off_t     st_size;        /* Total size, in bytes 
               blksize_t st_blksize;     /* Block size for filesystem I/O 
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated 

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. 

               struct timespec st_atim;  /* Time of last access 
               struct timespec st_mtim;  /* Time of last modification 
               struct timespec st_ctim;  /* Time of last status change 

           #define st_atime st_atim.tv_sec      /* Backward compatibility 
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };
           
           
st_dev This field describes the device on which this file
              resides.  (The major(3) and minor(3) macros may be useful
              to decompose the device ID in this field.)

       st_ino This field contains the file's inode number.

       st_mode
              This field contains the file type and mode.  See inode(7)
              for further information.

       st_nlink
              This field contains the number of hard links to the file.

       st_uid This field contains the user ID of the owner of the file.

       st_gid This field contains the ID of the group owner of the file.

       st_rdev
              This field describes the device that this file (inode)
              represents.

       st_size
              This field gives the size of the file (if it is a regular
              file or a symbolic link) in bytes.  The size of a symbolic
              link is the length of the pathname it contains, without a
              terminating null byte.

       st_blksize
              This field gives the "preferred" block size for efficient
              filesystem I/O.

       st_blocks
              This field indicates the number of blocks allocated to the
              file, in 512-byte units.  (This may be smaller than
              st_size/512 when the file has holes.)

       st_atime
              This is the time of the last access of file data.

       st_mtime
              This is the time of last modification of file data.

       st_ctime
              This is the file's last status change timestamp (time of
              last change to the inode).*/