#include "shell.h"
typedef struct node node;
struct node
{
    char name[MAX_ARRAY_SIZE];
    int num;
    int id;
    char status[10];
};
int compare (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void print_jobs(char str[][MAX_ARRAY_SIZE], int no_args)
{
    
    if (no_args == 1 )
    {
        int j = 0;
        for (int i = 0; i < no_bg_processes; i++)
        {
            char proc[200] = "/proc/";
            char st[6] = "/stat";
            int x = pro_ids[i];
            char pp[100];
            sprintf(pp, "%d", x);
            strcat(proc, pp);
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
                if (strcmp(options[2], "R") == 0 || strcmp(options[2], "S") == 0 || strcmp(options[2], "T") == 0)
                {
                    j++;
                }
                free(options);
            }
        }
       // printf("doone\n");
        node jobs[j];
        int check = 0;
        for (int k = 0; k < no_bg_processes, check < j; k++)
        {
            char proc[200] = "/proc/";
            char st[6] = "/stat";
            int x = pro_ids[k];
            char pp[100];
            sprintf(pp, "%d", x);
            strcat(proc, pp);
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
                if (strcmp(options[2], "R") == 0 || strcmp(options[2], "S")==0)
                {
                    strcpy(jobs[check].name, processes[k]);
                    jobs[check].id = pro_ids[k];
                    jobs[check].num = k + 1;
                    strcpy(jobs[check].status, "Running");
                    check++;
                }
                if (strcmp(options[2], "T") == 0)
                {
                    strcpy(jobs[check].name, processes[k]);
                    jobs[check].id = pro_ids[k];
                    jobs[check].num = k + 1;
                    strcpy(jobs[check].status, "Stopped");
                    check++;
                }
                free(options);
            }
        }
        qsort(jobs, j, sizeof(node), compare);
        for (int i = 0; i < j; i++)
        {
            printf("[%d] %s %s [%d]\n", jobs[i].num, jobs[i].status, jobs[i].name, jobs[i].id);
        }
    }
    else if (no_args==2 && strcmp (str[1],"-r")==0)
    {
        int j = 0;
        for (int i = 0; i < no_bg_processes; i++)
        {
            char proc[200] = "/proc/";
            char st[6] = "/stat";
            int x = pro_ids[i];
            char pp[100];
            sprintf(pp, "%d", x);
            strcat(proc, pp);
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
                if (strcmp(options[2], "R") == 0 || strcmp(options[2], "S") == 0 )
                {
                    j++;
                }
                free(options);
            }
        }
       // printf("doone\n");
        node jobs[j];
        int check = 0;
        for (int k = 0; k < no_bg_processes, check < j; k++)
        {
            char proc[200] = "/proc/";
            char st[6] = "/stat";
            int x = pro_ids[k];
            char pp[100];
            sprintf(pp, "%d", x);
            strcat(proc, pp);
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
                if (strcmp(options[2], "R") == 0 || strcmp(options[2], "S")==0)
                {
                    strcpy(jobs[check].name, processes[k]);
                    jobs[check].id = pro_ids[k];
                    jobs[check].num = k + 1;
                    strcpy(jobs[check].status, "Running");
                    check++;
                }
                
                free(options);
            }
        }
        qsort(jobs, j, sizeof(node), compare);
        for (int i = 0; i < j; i++)
        {
            printf("[%d] %s %s [%d]\n", jobs[i].num, jobs[i].status, jobs[i].name, jobs[i].id);
        }
    }
    else if (no_args==2 && strcmp(str[1],"-s")==0)
    {
        int j = 0;
        for (int i = 0; i < no_bg_processes; i++)
        {
            char proc[200] = "/proc/";
            char st[6] = "/stat";
            int x = pro_ids[i];
            char pp[100];
            sprintf(pp, "%d", x);
            strcat(proc, pp);
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
                if ( strcmp(options[2], "T") == 0)
                {
                    j++;
                }
                free(options);
            }
        }
       // printf("doone\n");
        node jobs[j];
        int check = 0;
        for (int k = 0; k < no_bg_processes, check < j; k++)
        {
            char proc[200] = "/proc/";
            char st[6] = "/stat";
            int x = pro_ids[k];
            char pp[100];
            sprintf(pp, "%d", x);
            strcat(proc, pp);
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
                    strcpy(jobs[check].name, processes[k]);
                    jobs[check].id = pro_ids[k];
                    jobs[check].num = k + 1;
                    strcpy(jobs[check].status, "Stopped");
                    check++;
                }
                free(options);
            }
        }
        qsort(jobs, j, sizeof(node), compare);
        for (int i = 0; i < j; i++)
        {
            printf("[%d] %s %s [%d]\n", jobs[i].num, jobs[i].status, jobs[i].name, jobs[i].id);
        }
    }
    else
    {
        printf("Error: Incorrect Command\n");
    }
    
    
}