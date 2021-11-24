#include "shell.h"
void cz()
{
    if(fg==-1)
    return;
    else if(fg==1 && pid>0)
    {
        kill(pid,SIGTSTP);
        pro_ids[no_bg_processes]=pid;
        strcpy(processes[no_bg_processes],fg_name);
        no_bg_processes++;
        //printf("%s\n",fg_name);
        fflush(stdout);
        
        return;
        
    }
    
}
void sig()
{
    if (fg == 1 && pid > 0)
    {
        kill(pid, SIGINT);
        printf("\n");
        fflush(stdout);
    }
    else
    {
        if (exiting != 1)
        {
            printf("\n");
            char current[MAX_ARRAY_SIZE];
            getcwd(current, MAX_ARRAY_SIZE);

            display(current, home_of_shell);
            fflush(stdout);
        }
    }

    return;
}
int main(int argc, char *argv[])
{
    CLR_SCR;
    write(1, "Welcome!\n", 10);

    char curr_dir[MAX_ARRAY_SIZE];

    getcwd(curr_dir, MAX_ARRAY_SIZE);

    strcpy(home_of_shell, curr_dir);

    no_bg_processes = 0;
    changed_dir = 0;
    exiting = 0;
    signal(SIGINT, sig);
    signal(SIGTSTP,cz);
    while (1)
    {
        display(curr_dir, home_of_shell);
        finish_bg();
        char *input = NULL;
        ssize_t len = 0;

        if(getline(&input, &len, stdin)==-1)
        {
            printf("\n");
            /*for (int v = 0; v < 100; v++)
            {
                if (pro_ids[v] != -1)
                    kill(pro_ids[v], SIGINT);
            }*/
            //CLR_SCR;
            
            exit(0);
        }
        //if(read(stdin,O_RDONLY)==0)
        //exit(0);
        //if(input==EOF)
        //exit(0);
        char *rest;
        char *token = strtok_r(input, ";", &rest);

        int count = 0;
        char buffer[MAX_NO_COMMANDS][MAX_ARRAY_SIZE];
        while (token != NULL)
        {

            strcpy(buffer[count], token);
            token = strtok_r(NULL, ";", &rest);
            count++;
        }
        execute(buffer, count);
    }

    return 0;
}