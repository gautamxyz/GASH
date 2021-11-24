#include"shell.h"

void pinfo_command(char str[][MAX_ARRAY_SIZE],int no_args)
{
    char proc[200]="/proc/";
    char st[6]="/stat";
    if(no_args==1)
    strcat(proc,"self");
    else
    {
        strcat(proc,str[1]);
    }
    strcat(proc,st);
    //printf("check\n");
    int f=open(proc,O_RDONLY);
    char buffer[MAX_ARRAY_SIZE];
    //printf("done\n");
    long long byte=read(f,&buffer,MAX_ARRAY_SIZE);
    if(byte==-1)
    {
        perror(str[1]);
        return;
    }
    //printf("see\n");
    char *info[100];//=(char*)malloc(100*sizeof(char));
    for(int i=0;i<100;i++)
    info[i]=(char*)malloc(MAX_ARRAY_SIZE*sizeof(char));

    int count=0;
    char*token=strtok(buffer," \t");
    while (token!=NULL)
    {
        
        strcpy(info[count],token);
        token=strtok(NULL," \t");
        count++;
    }
    if(no_args>1)
    printf("pid -- %s\nProcess Status -- %s\nmemory -- %s\nExecutable Path -- %s\n",info[0],info[2],info[22],info[1]);
    //free(info);
    else if (no_args==1)
    {
        printf("pid -- %s\nProcess Status -- %s+\nmemory -- %s\nExecutable Path -- %s\n",info[0],info[2],info[22],info[1]);
    }
    
    return ;
    
    
    
}