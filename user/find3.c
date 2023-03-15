#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int
match(char *filename, char *name) {
  return strcmp(filename, name) == 0;
}

// '.' Matches any single character.​​​​
// '*' Matches zero or more of the preceding element.
// int match(char* s, char* p) {//s=de.name p=name
//   if (!*p) return !*s;//return 1 when s is null and p is null 
//   if (*(p + 1) != '*') 
//     return *s == *p || (*p == '.' && *s != '\0') ? match(s + 1, p + 1) : 0; 
//   else 
//     return *s == *p || (*p == '.' && *s != '\0') ? match(s, p + 2) || match(s + 1, p) : match(s, p + 2);
//     //return (*s == *p || (*p == '.' && *s != '\0')) && match(s + 1, p) || match(s, p + 2);
// }


void
catdir(char *predix, char *name, char *buf)//dir de.name path
{
  memcpy(buf, predix, strlen(predix));//dir to path
  char *p = buf + strlen(predix);
  *p++ = '/';
  memcpy(p, name, strlen(name));
  p += strlen(name);
  *p++ = 0;//path=[dir/name0]
}


void
find(int fd, char *dir, char *name) {//dir fd ,dir,name
  struct dirent de;
//   struct dirent {
//   ushort inum;
//   char name[DIRSIZ];
// };

  
  while(read(fd, &de, sizeof(de)) == sizeof(de)) {//fd to de
    if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;//don't recurse to . ..
    struct stat st;
    char path[512];
    catdir(dir, de.name, path);
  //path=[dir/name0]
    if(de.inum == 0)
        continue;//file is not in use
    if(stat(path, &st) < 0){//info from filename 
        printf("find: cannot stat %s\n", path);
        continue;
    }

    // else{ int filefd=open(path,0); 
      // printf("fd=%d,inum=%d,de.name=%s,name=%s\n",filefd,de.inum,de.name,name);
      // printf("path=%s,dev=%d,inode number=%d,type=%d nlink=%d,size=%d\n",path,st.dev,st.ino,st.type,st.nlink,st.size);}
    if (st.type == T_FILE && match(de.name, name)) {
      printf("%s\n", path);
    } else if (st.type == T_DIR) {
      int subfd;
      if((subfd = open(path, 0)) < 0){
        // printf("find: cannot open %s\n", path);
        continue;
      }
      printf("path=%s\n",path);
      find(subfd, path, name);
    }

  }
}


int
main(int argc, char *argv[])
{
  if (argc != 3) {
    fprintf(2, "Usage: find dir name\n");
    exit(1);
  }

  char dir[DIRSIZ + 1];//The name is at most DIRSIZ (14) characters
  char name[DIRSIZ + 1];

  if (strlen(argv[1]) > DIRSIZ || strlen(argv[2]) > DIRSIZ) {
    fprintf(2, "dir or name too long...\n");
    exit(1);
  }

  memcpy(dir, argv[1], strlen(argv[1]));//memcpy(dest,src,size)
  memcpy(name, argv[2], strlen(argv[2]));
//find file name in  directory 

  int fd;
  struct stat st;
// struct stat {
//   int dev;     // File system's disk device
//   uint ino;    // Inode number
//   short type;  // Type of file
//   short nlink; // Number of links to file
//   uint64 size; // Size of file in bytes
// };

  if((fd = open(dir, 0)) < 0){//dir file descriptor
    fprintf(2, "find: cannot open %s\n", dir);
    exit(1);
  }

  if(fstat(fd, &st) < 0){//fstate infomation from file descriptor
    fprintf(2, "find: cannot stat %s\n", dir);
    close(fd);
    exit(1);
  }

  if (st.type != T_DIR) {
    printf("%s is not a dir\n", dir);
  } else {
    find(fd, dir, name);
  }
  
  exit(0);
}