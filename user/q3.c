#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        exit(1);
    }

    int pid = fork();
    if (pid == -1) {
        exit(1);
    }

    if (pid == 0) { // child process
        close(fd[0]); // close read end of pipe
        printf("hello\n");
        write(fd[1], "1", 1); // write to pipe to signal parent
        close(fd[1]);
    } else { // parent process
        close(fd[1]); // close write end of pipe
        char buf[1];
        read(fd[0], buf, 1); // wait for signal from child
        printf("goodbye\n");
        close(fd[0]);
    }

    return 0;
}
