#include "shell.h"

void finish_bg()
{

    int p,status;
    while ((p=waitpid(-1,&status,WNOHANG|WUNTRACED))>0)
    {
        
        if(WIFEXITED(status))
        {
            
            for(int i=0;i<no_bg_processes;i++)
            {
                if(p==pro_ids[i])
                {
                    //waitpid(p,0,0);
                    pro_ids[i]=-1;
                    fprintf(stderr,"%s with pid %d exited normally\n",processes[i],p);
                    break;
                }
            }
        }
        else if (WIFSIGNALED(status))
        {
            //waitpid(p,0,0);
            for(int i=0;i<no_bg_processes;i++)
            {
                if(p==pro_ids[i])
                {
                    //waitpid(p,0,0);
                    pro_ids[i]=-1;
                    fprintf(stderr,"%s with pid %d terminated\n",processes[i],p);
                    break;   
                }
            }
        }
        
    }
    
}
int bg_command(char str[][MAX_ARRAY_SIZE], int no_args)
{
    strcpy(str[no_args - 1], "\0");
    char *buffer[no_args];
    for (int i = 0; i < no_args; i++)
    {
        buffer[i]=(char*)malloc(MAX_ARRAY_SIZE*sizeof(char));
        strcpy(buffer[i], str[i]);
    }
    buffer[no_args-1]=NULL;
    //printf("done\n");
    //printf("%s\n",buffer[0]);
    
    pid = fork();
    if (pid < 0)
    {
        printf("error\n");
        return 0;
    }
    if (pid == 0)
    {
        setpgid(0,0);
       // close(STDERR_FILENO);
       bg=0;
        // x = execvp(buffer[0],buffer);
         //printf("done\n");
        if ((execvp(buffer[0],buffer))<0)
        {
            //perror("error");
            //
             printf("Error: Could not run background process\n");
            exit(1);
            //printf("%s",buffer[0]);
        }
        else 
        {
           
            printf("Started process %s with pid: %d\n",buffer[0],pid);
        }
        
            
        
        
        exit(0);
    }
    /*else
    {
        waitpid(pid,0,0);
    }*/
    
    return 0;
    
}
int fg_command(char str[][MAX_ARRAY_SIZE],int no_args)
{
    //strcpy(str[no_args - 1], "\0");
    char *buffer[no_args+1];
    for (int i = 0; i < no_args; i++)
    {
        buffer[i]=(char*)malloc(MAX_ARRAY_SIZE*sizeof(char));
        strcpy(buffer[i], str[i]);
    }
    buffer[no_args]=NULL;
    //printf("done\n");
    //printf("%s\n",buffer[0]);
    fg=1;
    pid = fork();
    if (pid < 0)
    {
        printf("error\n");
        return 0;
    }
    if (pid == 0)
    {
        //setpgid(0,0);
       // close(STDERR_FILENO);
       bg=0;
        // x = execvp(buffer[0],buffer);
         //printf("done\n");
        if ((execvp(buffer[0],buffer))<0)
        {
            //perror("error");
            //
            fg=-1;
             printf("Error: Command not found\n");
            exit(1);
            //printf("%s",buffer[0]);
        }
        else 
        {
           
            printf("Started process %s with pid: %d\n",buffer[0],pid);
        }
        
            
        
        
        exit(0);
    }
    return fg;

}