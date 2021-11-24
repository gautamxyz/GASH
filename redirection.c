#include "shell.h"
int parse_arg(char *t1, char **parts)
{
    int i = 0;
    char *token1 = strtok(t1, " \t\n");
    while (token1 != NULL)
    {
        parts[i] = (char *)malloc(400 * sizeof(char));
        strcpy(parts[i], token1);
        token1 = strtok(NULL, " \t\n");
        i++;
    }
    return i;
}
int check_redirection(char *stri)
{
    //  printf("enter\n");
    int inp = 0, outp1 = 0, outp2 = 0;
    for (int i = 0; i < strlen(stri); i++)
    {
        if (stri[i] == '<')
            inp++;
        else if (stri[i] == '>' && stri[i + 1] == '>')
        {
            outp2++;
            i++;
        }
        else if (stri[i] == '>')
        {
            outp1++;
        }
    }
    if (inp == 0 && outp1 == 0 && outp2 == 0)
        return -1;

    else if (inp == 0 && outp1 == 1)
    {
        char **args = (char **)malloc(100 * sizeof(char *));
        int j = 0;
        char *t1 = strtok(stri, ">");
        while (t1 != NULL)
        {
            args[j] = (char *)malloc(MAX_ARRAY_SIZE * sizeof(char));
            strcpy(args[j], t1);
            t1 = strtok(NULL, ">");
            j++;
        }
        char **first_part = (char **)malloc(100 * sizeof(char *));
        char **second_part = (char **)malloc(100 * sizeof(char *));
        int n1=parse_arg(args[0], first_part);
        int n2=parse_arg(args[j - 1], second_part);
        
        pid_t pp;
        pp = fork();
        if (pp < 0)
        {
            printf("Unexpected Error\n");
            return 0;
        }
        if (pp == 0)
        {
           // setpgid(0,0);
            if (second_part[0][strlen(second_part[0]) - 1] == '\n')
            {
                second_part[0][strlen(second_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int f = open(second_part[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXO | S_IRWXO);
            dup2(f, STDOUT_FILENO);
            /*char intm[1][MAX_ARRAY_SIZE];
            for(int i=0;i<n1;i++)
            {
                strcat(intm[0],first_part[i]);
                strcat(intm[0]," ");
            }*/
            //execute(intm,1);
            //dup2(STDOUT_FILENO,STDOUT_FILENO);
            if (execvp(first_part[0], first_part) < 0)
            {
                printf("gash: wrong command\n");
                exit(0);
            }
        }
        else
        {
            waitpid(pp,0,0);
        }
        
    }

    else if (inp == 0 && outp2 == 1)
    {
        char **args = (char **)malloc(100 * sizeof(char *));
        int j = 0;
        char *t1 = strtok(stri, ">");
        while (t1 != NULL)
        {
            args[j] = (char *)malloc(MAX_ARRAY_SIZE * sizeof(char));
            strcpy(args[j], t1);
            t1 = strtok(NULL, ">");
            j++;
        }
        char **first_part = (char **)malloc(100 * sizeof(char *));
        char **second_part = (char **)malloc(100 * sizeof(char *));
        parse_arg(args[0], first_part);
        parse_arg(args[j - 1], second_part);

        pid_t pp;
        pp = fork();
        if (pp < 0)
        {
            printf("Unexpected Error\n");
            return 0;
        }
        if (pp == 0)
        {
            if (second_part[0][strlen(second_part[0]) - 1] == '\n')
            {
                second_part[0][strlen(second_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int f = open(second_part[0], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXO | S_IRWXO);
            dup2(f, STDOUT_FILENO);
            if (execvp(first_part[0], first_part) < 0)
            {
                printf("gash: wrong command\n");
                exit(0);
            }
        }
        else
        {
            waitpid(pp,0,0);
        }
        
    }
    else if (inp == 1 && outp1 == 0 && outp2 == 0) //taking input from a file printing on stdout
    {
        char **args = (char **)malloc(100 * sizeof(char *));
        int j = 0;
        char *t1 = strtok(stri, "<");
        while (t1 != NULL)
        {
            args[j] = (char *)malloc(MAX_ARRAY_SIZE * sizeof(char));
            strcpy(args[j], t1);
            t1 = strtok(NULL, "<");
            j++;
        }
        char **first_part = (char **)malloc(100 * sizeof(char *));
        char **second_part = (char **)malloc(100 * sizeof(char *));
        int n1=parse_arg(args[0], first_part);
        int n2=parse_arg(args[j - 1], second_part);
        /*first_part[n1]=(char*)malloc(100*sizeof(char));
        first_part[n1]=NULL;
        second_part[n2]=(char*)malloc(100*sizeof(char));
        second_part[n2]=NULL;
        n1++;
        n2++;*/
        
        // printf("enter1\n");

        pid_t pp;
        pp = fork();
        //printf("enter2\n");
        setpgid(0, 0);
        if (pp < 0)
        {
            printf("Unexpected Error\n");
            exit(0);
        }
        if (pp == 0)
        {

            //fflush(stdout);
           /* int status;
            waitpid(-1,&status,WNOHANG|WUNTRACED);*/
            //printf("%stest\n",second_part[0]);
            if (second_part[0][strlen(second_part[0]) - 1] == '\n')
            {
                second_part[0][strlen(second_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int f = open(second_part[0], O_RDONLY);
            if (f < 0)
            {
                printf("%s: No such file or directory\n", second_part[0]);

                exit(0);
            }
            //CLR_SCR;
            //int h = dup(STDIN_FILENO);
            //close(h);
            dup2(f, STDIN_FILENO);
            //
            //dup2(STDIN_FILENO, STDIN_FILENO);
            close(f);
            /*char intm[1][MAX_ARRAY_SIZE];
            /*for(int i=0;i<n1;i++)
            {
                strcat(intm[0],first_part[i]);
                strcat(intm[0]," ");
            }*/
            //execute(intm,1);
            if (execvp(first_part[0], first_part) < 0)
            {
                printf("gash: wrong command\n");
                exit(0);
            }
        }
        else
        {
            waitpid(pp,0,0);
        }
        
    }

    else if (inp == 1 && outp1 == 1) // <,>
    {
        int cnt1 = 0, cnt2 = 0;
        for (int i = strlen(stri) - 1; i >= 0; i--)
        {
            if (stri[i] == '<')
                cnt1++;
            else if (stri[i] == '>')
            {
                break;
            }
        }
        for (int i = strlen(stri) - 1; i >= 0; i--)
        {
            if (stri[i] == '>')
            {
                cnt2++;
                stri[i] = '<';
            }
            else if (stri[i] == '<')
            {
                break;
            }
        }

        char **args = (char **)malloc(100 * sizeof(char *));
        int j = 0;
        char *t1 = strtok(stri, "<");
        while (t1 != NULL)
        {
            args[j] = (char *)malloc(MAX_ARRAY_SIZE * sizeof(char));
            strcpy(args[j], t1);
            t1 = strtok(NULL, "<");
            j++;
        }
        /*char **first_part = (char **)malloc(100 * sizeof(char *));
        char **second_part = (char **)malloc(100 * sizeof(char *));
        parse_arg(args[0], first_part);
        parse_arg(args[j - 1], second_part);*/

        pid_t pp;
        pp = fork();
        if (pp < 0)
        {
            printf("Unexpected Error\n");
            return 0;
        }
        if (pp == 0)
        {
            char **first_part = (char **)malloc(100 * sizeof(char *));
            char **second_part = (char **)malloc(100 * sizeof(char *));
            char **third_part = (char **)malloc(100 * sizeof(char *));
            parse_arg(args[j - cnt2 - 1], first_part);
            parse_arg(args[j - cnt1 - 1], second_part);
            parse_arg(args[0], third_part);

            if (first_part[0][strlen(first_part[0]) - 1] == '\n')
            {
                first_part[0][strlen(first_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int infile = open(first_part[0], O_RDONLY);
            if (infile < 0)
            {
                printf("%s: No such file or directory\n", first_part[0]);
                exit(0);
            }
            dup2(infile, STDIN_FILENO);

            if (second_part[0][strlen(second_part[0]) - 1] == '\n')
            {
                second_part[0][strlen(second_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int f = open(second_part[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXO | S_IRWXO);
            dup2(f, STDOUT_FILENO);
            if (execvp(third_part[0], third_part) < 0)
            {
                printf("gash: wrong command\n");
                exit(0);
            }
        }
        else
        {
            waitpid(pp,0,0);
        }
        
    }
    else if (inp == 1 && outp2 == 1) // <,>>
    {
        int cnt1 = 0, cnt2 = 0;
        for (int i = strlen(stri) - 1; i >= 0; i--)
        {
            if (stri[i] == '<')
                cnt1++;
            else if (stri[i] == '>')
            {
                break;
            }
        }
        for (int i = strlen(stri) - 1; i >= 0; i--)
        {
            if (stri[i] == '>')
            {
                cnt2++;
                stri[i] = '<';
            }
            else if (stri[i] == '<')
            {
                break;
            }
        }

        char **args = (char **)malloc(100 * sizeof(char *));
        int j = 0;
        char *t1 = strtok(stri, "<");
        while (t1 != NULL)
        {
            args[j] = (char *)malloc(MAX_ARRAY_SIZE * sizeof(char));
            strcpy(args[j], t1);
            t1 = strtok(NULL, "<");
            j++;
        }
        /*char **first_part = (char **)malloc(100 * sizeof(char *));
        char **second_part = (char **)malloc(100 * sizeof(char *));
        parse_arg(args[0], first_part);
        parse_arg(args[j - 1], second_part);*/

        pid_t pp;
        pp = fork();
        if (pp < 0)
        {
            printf("Unexpected Error\n");
            return 0;
        }
        if (pp == 0)
        {
            char **first_part = (char **)malloc(100 * sizeof(char *));
            char **second_part = (char **)malloc(100 * sizeof(char *));
            char **third_part = (char **)malloc(100 * sizeof(char *));
            parse_arg(args[j - cnt2], first_part);
            parse_arg(args[j - cnt1 - 1], second_part);
            parse_arg(args[0], third_part);

            if (first_part[0][strlen(first_part[0]) - 1] == '\n')
            {
                first_part[0][strlen(first_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int infile = open(first_part[0], O_RDONLY);
            if (infile < 0)
            {
                printf("%s: No such file or directory\n", first_part[0]);
                exit(0);
            }
            dup2(infile, STDIN_FILENO);

            if (second_part[0][strlen(second_part[0]) - 1] == '\n')
            {
                second_part[0][strlen(second_part[0]) - 1] = '\0';
                /*char buffer[MAX_ARRAY_SIZE];
                for(int i=0;i<strlen(second_part[0])-1;i++)
                buffer[i]=second_part[0][i];*/
            }
            int f = open(second_part[0], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXO | S_IRWXO);
            dup2(f, STDOUT_FILENO);
            if (execvp(third_part[0], third_part) < 0)
            {
                printf("gash: wrong command\n");
                exit(0);
            }
        }
        else
        {
            waitpid(pp,0,0);
        }
        
    }
    else
    {
        printf("gash: Incorrect Command\n");
        return 0;
    }
    

    return 0;
}