#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXSIZE 16
int 
main(){
    int p[2];
    char buf[MAXSIZE];
    pipe(p);
    if(fork()==0){
        int pid=getpid();
        read(p[0],buf,1);
        printf("%d: received ping\n",pid);
        write(p[1],buf,1);
        close(p[1]);
    }
    else{
        int pid=getpid();
        write(p[1],buf,1);
        wait(0);
        read(p[0],buf,1);
        printf("%d: received pong\n",pid);
    }
    printf("OK\n");
    exit(0);
}