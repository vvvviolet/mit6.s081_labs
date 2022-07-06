#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

void 
find(char*path,char*name){
    struct stat st;
    int fd;
    struct dirent de;
    // printf("path: %s\n",path);
    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        exit(0);
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        exit(0);
    }

    if(st.type==T_DIR){
        char buf[512], *p=0;
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){//当前目录里的目录项
            memmove(p, de.name, strlen(de.name));
            p[strlen(de.name)] = 0;
            // printf("p: %s\n",p);
            // printf("buf: %s\n",buf);
            //buf: 绝对路径表示的文件名
            if(stat(buf, &st) < 0){
                printf("find: cannot stat %s\n", buf);
                continue;
            }
            if(st.type==T_FILE&&strcmp(de.name,name)==0){
                printf("%s\n", buf);
            }
            else if(st.type==T_DIR&&strcmp(de.name,".")&&strcmp(de.name,"..")&&strlen(de.name)){
                find(buf,name);
            }
        }
    }else if (st.type==T_FILE)
    {
        // printf("file: %s\n", path);
        char*p=path+strlen(path);
        while(*p!='/'&&p>=path)
            p--;
        
        p++;        
        // printf("p: %s\n", p);
        if(strcmp(p,name)==0){
            printf("%s\n", p);
        }
    }
    
}

int 
main(int argc,char*argv[]){
    if(argc<3){
        printf("usage: find <path> <file>\n");
        exit(0);
    }
    char* path = argv[1];
    char* name = argv[2];
    find(path,name);
    exit(0);
}