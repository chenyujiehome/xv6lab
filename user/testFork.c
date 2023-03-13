#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char const *argv[]) {
    char buf[64];
    int c2p[2];
    pipe(c2p);
if(!fork()){
    close(c2p[0]);
write(c2p[1],"ping",4);
exit(0);


}
close(c2p[1]);
read(c2p[0],buf,4);
printf("%s\n",buf);
exit(0);
}