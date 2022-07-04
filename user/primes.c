#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
primes(int p[]){
   int num=0;
   read(p[0],&num,sizeof(int));//经过上一个筛选，第一个一定是质数
   if(num==0){
     exit(0);
   }
   printf("prime %d\n",num); 
   int p1[2];
   int buf[35];
   int tp=0;
   int prime=num;
   pipe(p1);
   
   while(read(p[0],&num,sizeof(int))){
      buf[tp++]=num;
   }
   close(p[0]);
   for(int i=0;i<tp;i++){
   if(buf[i]%prime){
        write(p1[1],&buf[i],sizeof(int));
    }
   }
   close(p1[1]);
   if(fork()==0){
     primes(p1);
   }
   wait(0);
   exit(0);
}


int
main(){
    int p[2];
    pipe(p);
    int i;
    //初始化
    for(i=2;i<36;i++){
        write(p[1],&i,sizeof(int));
    }
    close(p[1]);
    if(fork()==0){        
        primes(p);
    }
    wait(0);
    printf("OK\n");
    exit(0);
}