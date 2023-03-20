#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
int x =100;

  if (!fork()) {
    x=0;
   printf("in child process,x=%d\n",x);
  } else {

    wait(0);

    x=200;
   printf("in parent process,x=%d\n",x);

  }

  exit(0);
}
