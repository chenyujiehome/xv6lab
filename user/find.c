#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

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
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
find(char *path,char *filename)
{
  char buf[50], *p;
  int fd;
  struct dirent de;
  //   struct dirent {
//   ushort inum;
//   char name[DIRSIZ];
// };
  struct stat st;         
     // struct stat {
//   int dev;     // File system's disk device
//   uint ino;    // Inode number
//   short type;  // Type of file
//   short nlink; // Number of links to file
//   uint64 size; // Size of file in bytes
// };
  if((fd = open(path, 0)) < 0){//path is directory
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
if (st.type!= T_DIR)
{
  exit(1);
}


 


    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
    }
    strcpy(buf, path);//path to buf
    p = buf+strlen(buf);
    *p++ = '/';//p=[path/]
    while(read(fd, &de, sizeof(de)) == sizeof(de)){//fd is descriptor of directory,de is file of directory
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }
      if (st.type == T_DIR && *p != '.') {
        // char dir[50];
// memcpy(dir,buf,sizeof(buf));
// printf("dir=%s,buf=%s,strcmp=%d\n",dir,buf,strcmp(dir,buf));
          find(buf, filename);
      } else if (strcmp(p, filename) == 0) {
        printf("%s\n", buf);
      }
    }
  
  close(fd);
}

int
main(int argc, char *argv[])
{ if(argc !=3){
    printf("find need 2 arguements");
    exit(1);
  }  
  char path[512];
  int fd;
    struct stat st;
  memcpy(path, argv[1], strlen(argv[1]));//memcpy(dest,src,size)


  if((fd = open(argv[1], 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
   exit(1);
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
  exit(1);
  }

  if (st.type!=T_DIR)
  {
    printf("first argument isn't directory");
    exit(1);
  }
  
    find(path,argv[2]);
  exit(0);
}
