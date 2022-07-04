#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLEN 30

int
main(int argc,char*argv[]){
    //接收重定向方式获得的参数
    char buf[MAXLEN];
    read(0,buf,MAXLEN);

    //接收参数方式获得的参数
    char*xargv[MAXARG];
    int xargc=0;
    for(int i=1;i<argc;i++){
        xargv[xargc++]=argv[i];
    }
    // for(int i=0;i<argc;i++){
    //     printf("xargv[%d]:%s\n",i,xargv[i]);
    // }
    char* p = buf;
    int len = strlen(p);
    for(int i=0;i<len;i++){
        if(buf[i]=='\n'){
            if(fork()==0){
                buf[i]=0;
                // printf("p :%s\n",p);
                xargv[xargc++]=p;
                exec(xargv[0],xargv);
                printf("exec %s failed\n",xargv[0]);
                exit(0);
            }
            p=buf+i+1;
            wait(0);
        }
    }

    wait(0);   
    exit(0);
}