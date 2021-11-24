#include"shell.h"

int check_piping(char * command)
{
    int check=0;
    for(int i=0;i<strlen(command);i++)
    {
        if(command[i]=='|')
        {
            check=1;
            break;
        }
    }
    if(check!=1)
    return -1;

    char ** string =(char**) malloc(100*sizeof(char*));
    int j=0;
    char *t=strtok(command,"|");
    while (t!=NULL)
    {
        string[j]=(char*)malloc(MAX_ARRAY_SIZE*sizeof(char));
        strcpy(string[j],t);
        t=strtok(NULL,"|");
        j++;
    }
    j--;
    int fd1[2],fd2[2];
    for(int i=0;i<j+1;i++)
    {
        if(i%2==0)
        {
            if(pipe(fd1)<0)
            {
                printf("Error in piping\n");
                return 0;
            }
        }
        else
        {
            if(pipe(fd2)<0)
            {
                printf("Error in piping\n");
                return 0;
            }
        }

        pid_t pp=fork();
        if(pp<0)
        {
            printf("Unexpected Error\n");
            return 0;
        }
        if(pp==0)
        {
            if(i%2==0)
            {
                if(i>0)
                {
                    dup2(fd2[0],STDIN_FILENO);
                }
                if(i!=j)
                {
                    dup2(fd1[1],STDOUT_FILENO);
                }
            }
            else
            {
                dup2(fd1[0],STDIN_FILENO);
                if(i!=j)
                {
                    dup2(fd2[1],STDOUT_FILENO);
                }
            }
            if(check_redirection(string[i])==-1)
            {
                char ** buffer=(char**)malloc(100*sizeof(char*));
                parse_arg(string[i],buffer);
                if(execvp(buffer[0],buffer)<0)
                printf("gash: Wrong Command\n");
            }
            exit(0);
            
        }
        else
        {
            if(i%2==0)
            {
                if(i!=0)
                {
                    close(fd2[0]);
                }
                if(i!=j)
                close(fd1[1]);
            }
            else
            {
                close(fd1[0]);
                if(i!=j)
                {
                    close(fd2[1]);
                }
            }
            wait(NULL);
            
        }
        
        
    }
    
}