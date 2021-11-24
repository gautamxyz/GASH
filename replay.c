#include "shell.h"
void replay(char str[][MAX_ARRAY_SIZE], int no_args)
{
    int index_c = -1, index_i = -1, index_p = -1;
    int count[3]={0};
    for (int i = 0; i < no_args; i++)
    {
        if (strcmp(str[i], "-command") == 0)
        {
            index_c = i;
            count[0]++;
        }
        else if (strcmp(str[i], "-interval") == 0)
        {
            index_i = i;
            count[1]++;
        }
        else if (strcmp(str[i], "-period") == 0)
        {
            index_p = i;
            count[2]++;
        }
    }
    //printf("%d\n",no_args);
    if(count[0]==1 && count[1]==1 && count[2]==1 && index_c==1 && index_p-index_i==2 && index_p==no_args-2)
    {
        char **buf=(char**)malloc((100)*sizeof(char*));
        int j=0;
        for(int i=index_c+1;i<index_i;i++)
        {
            buf[j]=(char*)malloc(400*sizeof(char));
            strcpy(buf[j],str[i]);
            j++;
        }
        buf[j]=NULL;
        int pd,in;
        sscanf(str[index_p+1],"%d",&pd);
        sscanf(str[index_i+1],"%d",&in);
        int tms=pd/in;
        /*pid_t pp=fork();
        if(pp==-1)
        {
            printf("Unexpected Error\n");
            return;
        }
        if(pp==0)
        {
            setpgid(0,0);
            close(STDERR_FILENO);*/
           
            
           while(tms>0)
            {
                sleep(in);
                pid_t p=fork();
                if(p==-1)
                {
                    printf("Unexpected Error\n");
                    return;
                }
                if(p==0)
                {
                    if(execvp(buf[0],buf)==-1)
                    {
                        printf("Error\n");
                        
                    }
                    exit(0);
                }
                else
                {
                    waitpid(p,0,0);
                }
                //sleep(in);
                tms--;
                
            }
        /*}
        else
        {
            waitpid(pp,0,0);
        }
        */
    }
    else
    {
        printf("Error: Command not found\n");
    }
    return;
    
}