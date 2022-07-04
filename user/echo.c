#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define NULL 0
#define MAXLEN 1024
// 07042022
// 无法实现转义\n和双引号功能，重新实现 lab1-xargs
// 添加功能： 转义\n，双引号
int
main(int argc, char *argv[])
{
  if(argc<2){
    printf("usage: echo <arg1> [arg2] ...  \n");
    exit(0);
  }
  argv++;
  argc--;//丢弃argv[0]
  
  //有双引号
  if(argv[0][0]=='"'
  &&argv[argc - 1][strlen(argv[argc - 1]) - 1]=='"'
  ){
    //如果多个入参，拼接
    char parsed[MAXLEN];
    // char*p=argv[0]+strlen(argv[0]);
    char*p=parsed;
    strcpy(p,argv[0]+1);
    // printf("0: %s\n",p);
    for(int i=1;i<argc;i++){
      p=p+strlen(p);
      *p=' ';
      p++;
      strcpy(p,argv[i]);
      // printf("argv[%d] %s\n",i,argv[i]);
      // printf("p: %s\n",p);
    }
    *(p+strlen(p)-1)=0;
    // printf("parsed: *%s*\n",parsed);
    p=parsed;
    for(int i=0;i<strlen(p);i++){
      if(p[i]=='\\' && i+1 < strlen(p) && p[i + 1] == 'n'){
        write(1,"\n",1);
        i++;
      }else{
        write(1,&p[i],1);
      }
    }
    write(1,"\n",1);
  }
  //无双引号
  else{
    for(int i=0;i<argc;i++){
      write(1,argv[i],strlen(argv[i]));
      if(argc>0){
        write(1," ",1);
      }
    }
    write(1,"\n",1);
  }
  exit(0);
}
