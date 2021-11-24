#include "shell.h"

void display(char curr_dir[],char home_of_shell[])
{
    char dir[MAX_ARRAY_SIZE];
    char *user=getenv("LOGNAME");
    char machine[MAX_ARRAY_SIZE];
    gethostname(machine,MAX_ARRAY_SIZE);
    getcwd(curr_dir,MAX_ARRAY_SIZE);
    if(strlen(curr_dir)>=strlen(home_of_shell))
    {
        printf(ANSI_COLOR_CYAN"<%s@%s:~"ANSI_COLOR_RESET,user,machine);
        for(int i=strlen(home_of_shell);i<strlen(curr_dir);i++)
        {
            printf(ANSI_COLOR_CYAN"%c"ANSI_COLOR_RESET,curr_dir[i]);
        }
    }
    else
    {
        printf(ANSI_COLOR_CYAN"<%s@%s:~"ANSI_COLOR_RESET,user,machine);
        for(int i=0;i<strlen(curr_dir);i++)
        {
            printf(ANSI_COLOR_CYAN"%c" ANSI_COLOR_RESET,curr_dir[i]);
        }
    }
    printf(ANSI_COLOR_CYAN"> " ANSI_COLOR_RESET);
    fflush(stdout);
    /*if(strcmp(curr_dir,home_of_shell)==0)
    {
        printf(ANSI_COLOR_CYAN "<%s@%s:~> ",user,machine);
        dir[0]='\0';
    
    }
    

    else if(strlen(curr_dir)>strlen(home_of_shell))
    {
        changed_dir=1;
        int len=strlen(curr_dir)-strlen(home_of_shell);
        int i;
        for( i=0;i<len;i++)
        {
            dir[i]=curr_dir[i+strlen(home_of_shell)];
        }
        dir[i]='\0';
        printf(ANSI_COLOR_CYAN "<%s@%s:~%s> ",user,machine,dir);
        
    }
    else if(strcmp(curr_dir,home_of_shell)<0)
    {
        printf(ANSI_COLOR_CYAN "<%s@%s:%s> ",user,machine,curr_dir);
        changed_dir=1;
    }
    
    //printf("%s  %s   %ld\n",curr_dir,dir,strlen(dir));*/
    
   
    return;
}