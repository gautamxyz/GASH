#include "shell.h"

void sig2(char str[][MAX_ARRAY_SIZE], int no_args)
{
    if (no_args != 3)
    {
        printf("Error: Incorrect number of arguments\n");
        return;
    }
    int signall, pp;
    sscanf(str[1], "%d", &pp);
    if (pp == 0 || pp > no_bg_processes)
    {
        printf("Error: Incorrect job number\n");
        return;
    }
    sscanf(str[2], "%d", &signall);

    int p = pro_ids[pp - 1];
    kill(p, signall);
    return;
}

void handle_fg(char str[][MAX_ARRAY_SIZE], int no_args)
{
    pid_t pi = getpid();
    if (no_args != 2)
    {
        printf("Error: Incorrect number of arguments\n");
        return;
    }
    int pp;
    sscanf(str[1], "%d", &pp);
    if (pp == 0 || pp > no_bg_processes)
    {
        printf("Error: Incorrect job number\n");
        return;
    }
    pid_t pidnumber;
    pidnumber = pro_ids[pp - 1];

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pidnumber);
    //signal(SIGTTOU, SIG_DFL);

    /* char proc[200] = "/proc/";
    char st[6] = "/stat";
    int x = pidnumber;
    char p[100];
    sprintf(p, "%d", x);
    strcat(proc, p);
    strcat(proc, st);

    int f = open(proc, O_RDONLY);
    if (f != -1)
    {
        char buffer[MAX_ARRAY_SIZE];
        int byte = read(f, &buffer, MAX_ARRAY_SIZE);
        char **options = (char **)malloc(50 * sizeof(char *));
        for (int k = 0; k < 50; k++)
        {
            options[k] = (char *)malloc(500 * sizeof(char));
        }
        parse_arg(buffer, options);

        if (strcmp(options[2], "T") == 0)
        {
            
        }
        free(options);
    }*/
    kill(pidnumber, SIGCONT);
    pro_ids[pp - 1] = -1;
    int w;
    pid = pidnumber;
    waitpid(pidnumber, &w, WUNTRACED);
    //signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    return;
}

void handle_bg(char str[][MAX_ARRAY_SIZE], int no_args)
{
    if (no_args != 2)
    {
        printf("Error: Incorrect number of arguments\n");
        return;
    }
    int pp;
    sscanf(str[1], "%d", &pp);
    if (pp <= 0 || pp > no_bg_processes)
    {
        printf("Error:Incorrect job number\n");
        return;
    }
    pid_t p = pro_ids[pp - 1];
    if (p != -1)
    {
        kill(p, SIGTTIN);
        kill(p, SIGCONT);
    }
    else
    {
        printf("Error:Incorrect job number\n");
    }
    

    return;
}