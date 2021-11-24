#include "shell.h"

void repeat(char A[][MAX_ARRAY_SIZE], int y)
{
    int z = 0;
    char B[1][MAX_ARRAY_SIZE];
    while (z < y)
    {
        strcpy(B[0], A[0]);
        execute(B, 1);
        //printf("%s\n",A[0]);
        z++;
    }
    //
}
void execute(char buffer[][MAX_ARRAY_SIZE], int count)
{
    int x = 1;
    for (int i = 0; i < count; i++)
    {
        char *command =malloc(MAX_ARRAY_SIZE*sizeof(char));
        strcpy(command,buffer[i]);
        int re=check_piping(command);
        free(command);
        if(re!=-1)
        continue;
        char *stri = malloc(MAX_ARRAY_SIZE * sizeof(char));
        strcpy(stri, buffer[i]);
        int ret = check_redirection(stri);
        //printf("ret\n");
        
        free(stri);
        if (ret != -1)
        {
           // exit(0);
            continue;
        }
        char *rest;
        char *tok = strtok_r(buffer[i], " \t", &rest);
        int j = 0;
        char str[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
        while (tok != NULL)
        {
            strcpy(str[j], tok);
            if (str[j][strlen(str[j]) - 1] == '\n')
                str[j][strlen(str[j]) - 1] = '\0';
            j++;
            tok = strtok_r(NULL, " \t", &rest);
        }
        int no_args = j;
        for (int i = j; j < MAX_ARRAY_SIZE; j++)
        {
            strcpy(str[j], "\0");
        }
        if (strcmp(str[no_args - 1], "\0") == 0)
        {
            //strcpy(str[no_args-1],"\0");
            no_args--;
        }
        if (strcmp(str[0], "exit") == 0)
        {
            exiting = 1;
            for (int v = 0; v < 100; v++)
            {
                if (pro_ids[v] != -1)
                    kill(pro_ids[v], SIGINT);
            }
            //CLR_SCR;
            exit(0);
        }
        if (strcmp(str[0], "cd") == 0)
        {
            /*if (str[1][strlen(str[1]) - 1] == '\n')
                str[1][strlen(str[1]) - 1] = '\0';*/
            if (no_args > 2)
            {
                printf("gash: cd: too many arguments %sdone\n", str[2]);
            }
            else if (strcmp(str[1], "~") == 0 || strcmp(str[1], "\0") == 0)
            {
                //if(changed_dir!=0)
                changed_dir = 1;
                getcwd(previous_dir, MAX_ARRAY_SIZE);
                strcpy(str[1], home_of_shell);
                x = chdir(str[1]);
            }
            else if (strcmp(str[1], "-") == 0)
            {
                if (changed_dir != 0)
                {
                    char buffer[MAX_ARRAY_SIZE];
                    strcpy(buffer, previous_dir);
                    getcwd(previous_dir, MAX_ARRAY_SIZE);
                    x = chdir(buffer);
                    printf("%s\n", buffer);
                }
                else
                {
                    printf("gash: cd: OLDPWD not set\n");
                }
            }
            else
            {
                getcwd(previous_dir, MAX_ARRAY_SIZE);

                x = chdir(str[1]);
                if (x == -1)
                {

                    perror(str[1]);
                }
                if (x != -1)
                    changed_dir = 1;
            }
        }
        //printf("%s\n",str[0]);

        //printf("%d\n",x);
        else if (strcmp(str[0], "pwd") == 0)
        {
            char dir[MAX_ARRAY_SIZE];
            getcwd(dir, MAX_ARRAY_SIZE);
            printf("%s\n", dir);
        }
        else if (strcmp("clear", str[0]) == 0)
        {
            CLR_SCR;
        }
        else if (strcmp(str[0], "echo") == 0)
        {
            for (int b = 1; b < no_args; b++)
            {
                if (strcmp(str[b], "\0") == 0)
                {

                    break;
                }
                printf("%s ", str[b]);
            }
            printf("\n");
        }
        else if (strcmp(str[0], "ls") == 0)
        {
            ls_command(str, no_args);
        }
        else if (strcmp(str[no_args - 1], "&") == 0)
        {
            // printf("hi\n");
            int x = bg_command(str, no_args);
            if (bg == 0)
            {
                pro_ids[no_bg_processes] = pid;
                for (int h = 0; h < no_args - 1; h++)
                {

                    strcat(processes[no_bg_processes], str[h]);
                    if (h != no_args - 2)
                        strcat(processes[no_bg_processes], " ");
                }
                no_bg_processes++;
                printf("%d\n", pid);
            }
        }
        else if (strcmp(str[0], "pinfo") == 0)
        {
            pinfo_command(str, no_args);
        }
        else if (strcmp(str[0], "repeat") == 0)
        {
            //repeat=1;
            int y = atoi(str[1]);
            //int z=0;
            char A[2][MAX_ARRAY_SIZE];

            int z = 0;
            for (int l = 2; l < no_args; l++)
            {
                for (int m = 0; m < strlen(str[l]); m++)
                {
                    A[0][z] = str[l][m];
                    z++;
                }
                if (l != no_args - 1)
                {
                    A[0][z] = ' ';
                    z++;
                }
                else
                {
                    A[0][z] = '\0';
                }
            }
            strcpy(A[1], "\0");
            repeat(A, y);
            // no_args-=2;
            /*while (z<y)
            {
                execute(A,1);
                z++;
            }*/
            //repeat=0;
        }
        else if (strcmp(str[0],"jobs")==0)
        {
            print_jobs(str,no_args);
        }
        else if (strcmp(str[0],"sig")==0)
        {
            sig2(str,no_args);
        }
        else if (strcmp(str[0],"fg")==0)
        {
            handle_fg(str,no_args);
        }
        else if (strcmp(str[0],"bg")==0)
        {
            handle_bg(str,no_args);
        }
        else if (strcmp(str[0],"replay")==0)
        {
            replay(str,no_args);
        }
        
               
        else
        {
            int x = fg_command(str, no_args);
            if (fg == 1)
            {
                strcpy(fg_name, str[0]);
                for (int h = 1; h < no_args - 1; h++)
                {

                    strcat(fg_name, str[h]);
                    if (h != no_args - 2)
                        strcat(fg_name, " ");
                }
                int status;
                waitpid(pid, &status, WUNTRACED);
                //printf("%s done\n",fg_name);
                fg = -1;
            }
        }
    }
    //printf("%s\n",str[1]);
    return;
}