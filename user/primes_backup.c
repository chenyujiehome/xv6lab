#include "kernel/types.h"
#include "user/user.h"
void exec_pipe(int fd)
{
    int num;
    read(fd, &num, 4);//output to num
    printf("prime %d\n", num);

    int p[2];
    pipe(p);//new pipe
    int tmp = -1;
    while (1) {
        int n = read(fd, &tmp, 4);//n=bytes tmp=last p[0]
        if (n<= 0) {
            break;
        }
        if (tmp % num != 0) {//num=last output prime
            //printf(“%d writing %d and n is: %d\n”, getpid(), tmp, n);*
            write(p[1], &tmp, 4);
        }
    }
    if (tmp == -1) {
        close(p[1]);
        close(p[0]);
        close(fd);
        return;
    }
    // int pid = fork();
    // if (pid == 0) {
        close(p[1]);
        close(fd);
        exec_pipe(p[0]);
        close(p[0]);
//     }
//     else {
//         close(p[1]);
//         close(p[0]);
//         close(fd);
//         wait(0);
//     }
}
int
main(int argc, char const * argv[])
{
  int p[2];
  pipe(p);//build a pipe to communicate
  for (int i = 2; i<35; i++) {
      int n = i;
      write(p[1], &n, 4);//input
  }
  close(p[1]);//close write
  exec_pipe(p[0]);//excuting
  close(p[0]);

  exit(0);
}