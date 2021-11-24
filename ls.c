#include "shell.h"

void ls_command(char str[][MAX_ARRAY_SIZE], int no_args)
{
    DIR *dir;
    struct dirent *d;
    struct tm *t;
    char find_dir[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    char date_modified[MAX_ARRAY_SIZE];
    struct stat info;
    int l = 0, a = 0;

    int opt;

    
    int i = 1;
    int j = 0;

    while (i < no_args)
    {
        if (strcmp(str[i], "-l") == 0)
            l++;
        else if (strcmp(str[i], "-a") == 0)
        {
            a++;
        }
        else if (strcmp(str[i], "-la") == 0 || strcmp(str[i], "-al") == 0)
        {
            a++;
            l++;
        }
        else
        {
            if (strcmp(str[i], "~") == 0)
            {
                strcpy(find_dir[j], home_of_shell);
            }
            else
            {
                strcpy(find_dir[j], str[i]);
            }

            j++;
        }
        i++;
    }

    if (l == 0 && a == 0) //ls, ls ~ on all dirs
    {
        if (j > 1)
        {
            int k = 0;
            while (k < j)
            {

                //getcwd(find_dir, MAX_ARRAY_SIZE);
                int fil = 0;
                dir = opendir(find_dir[k]);
                if (dir == NULL)
                {
                    fil = open(find_dir[k], O_RDONLY);
                    if (fil != -1)
                    {
                        ls_for_file(find_dir[k], l, a);
                        close(fil);
                        k++;
                        continue;
                    }
                }
                if (dir == NULL && fil == -1)
                {
                    perror(find_dir[k]);
                    k++;
                    continue;
                }
                printf("%s:\n", find_dir[k]);
                while ((d = readdir(dir)) != NULL)
                {
                    if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0|| d->d_name[0]=='.')
                        continue;
                    printf("%s\n", d->d_name);
                }
                closedir(dir);
                k++;
                printf("\n");
            }
        }
        else if (j == 1)
        {
            int k = 0;
            while (k < j)
            {
                int fil = 0;
                dir = opendir(find_dir[0]);
                if (dir == NULL)
                {
                    fil = open(find_dir[k], O_RDONLY);
                    if (fil != -1)
                    {
                        ls_for_file(find_dir[k], l, a);
                        close(fil);
                        k++;
                        continue;
                    }
                }
                if (dir == NULL && fil == -1)
                {
                    perror(find_dir[0]);

                    k++;
                    continue;
                }
                //printf("%s:\n", find_dir[0]);
                while ((d = readdir(dir)) != NULL)
                {
                    if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 ||d->d_name[0]=='.')
                        continue;
                    printf("%s\n", d->d_name);
                }
                closedir(dir);
                k++;
            }
        }
        else if (j == 0)
        {
            //dir = opendir(home_of_shell);
            // printf("%s:\n", find_dir[k]);
            getcwd(find_dir[0], MAX_ARRAY_SIZE);
            dir = opendir(find_dir[0]);
            while ((d = readdir(dir)) != NULL)
            {
                if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || d->d_name[0]=='.')
                    continue;
                printf("%s\n", d->d_name);
            }
            closedir(dir);
        }
    }
    else if (a != 0 && l == 0) //ls -a
    {
        if (j > 1)
        {
            int k = 0;
            while (k < j)
            {

                //getcwd(find_dir, MAX_ARRAY_SIZE);
                int fil = 0;
                dir = opendir(find_dir[k]);
                if (dir == NULL)
                {
                    fil = open(find_dir[k], O_RDONLY);
                    if (fil != -1)
                    {
                        ls_for_file(find_dir[k], l, a);
                        close(fil);
                        k++;
                        continue;
                    }
                }
                if (dir == NULL && fil == -1)
                {
                    perror(find_dir[k]);
                    k++;
                    continue;
                }
                printf("%s:\n", find_dir[k]);
                while ((d = readdir(dir)) != NULL)
                {
                    /*if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                        continue;*/
                    printf("%s\n", d->d_name);
                }
                closedir(dir);
                k++;
                printf("\n");
            }
        }
        else if (j == 1)
        {
            int k = 0;
            while (k < j)
            {
                int fil = 0;
                dir = opendir(find_dir[0]);
                if (dir == NULL)
                {
                    fil = open(find_dir[k], O_RDONLY);
                    if (fil != -1)
                    {
                        ls_for_file(find_dir[k], l, a);
                        close(fil);
                        k++;
                        continue;
                    }
                }
                if (dir == NULL && fil == -1)
                {
                    perror(find_dir[0]);

                    k++;
                    continue;
                }
                //printf("%s:\n", find_dir[0]);
                while ((d = readdir(dir)) != NULL)
                {
                    /*if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                    continue;*/
                    printf("%s\n", d->d_name);
                }
                closedir(dir);
                k++;
            }
        }
        else if (j == 0)
        {
            getcwd(find_dir[0], MAX_ARRAY_SIZE);
            dir = opendir(find_dir[0]);
            while ((d = readdir(dir)) != NULL)
            {
                /*if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                    continue;*/
                printf("%s\n", d->d_name);
            }
            closedir(dir);
        }
    }

    else if (l != 0) //ls -l
    {
        char curr[MAX_ARRAY_SIZE];
        getcwd(curr, MAX_ARRAY_SIZE);
        if (j >= 1)
        {
            int k = 0;
            while (k < j)
            {

                char present[MAX_ARRAY_SIZE];
                strcpy(present, curr);
                //getcwd(find_dir, MAX_ARRAY_SIZE);
                strcat(present, "/");
                strcat(present, find_dir[k]);
                int fil=0;
                dir = opendir(present);
                if (dir == NULL)
                {
                    fil = open(find_dir[k], O_RDONLY);
                    if (fil != -1)
                    {
                        ls_for_file(find_dir[k], l, a);
                        close(fil);
                        k++;
                        continue;
                    }
                }
                if (dir == NULL && fil == -1)
                {
                    perror(find_dir[k]);
                    k++;
                    continue;
                }
                if (j > 1)
                    printf("%s:\n", find_dir[k]);
                long long block = 0;
                while ((d = readdir(dir)) != NULL)
                {
                    char path[MAX_ARRAY_SIZE];
                    strcpy(path, present);
                    strcat(path, "/");
                    //strcat(path,find_dir[k]);
                    //strcat(path,"/");
                    strcat(path, d->d_name);
                    if (a == 0 && (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || d->d_name[0]=='.'))
                        continue;
                    //struct stat info;
                    stat(path, &info);
                    block = block + info.st_blocks;
                }
                closedir(dir);
                printf("total %lld\n", block / 2);
                dir = opendir(present);

                while ((d = readdir(dir)) != NULL)
                {
                    char path[MAX_ARRAY_SIZE];
                    strcpy(path, present);
                    strcat(path, "/");
                    //strcat(path,find_dir[k]);
                    //strcat(path,"/");
                    strcat(path, d->d_name);
                    if (a == 0 && (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || d->d_name[0]=='.'))
                        continue;
                    //struct stat info;
                    stat(path, &info);
                    printf((S_ISDIR(info.st_mode)) ? "d" : "-");
                    printf((info.st_mode & S_IRUSR) ? "r" : "-");
                    printf((info.st_mode & S_IWUSR) ? "w" : "-");
                    printf((info.st_mode & S_IXUSR) ? "x" : "-");
                    printf((info.st_mode & S_IRGRP) ? "r" : "-");
                    printf((info.st_mode & S_IWGRP) ? "w" : "-");
                    printf((info.st_mode & S_IXGRP) ? "x" : "-");
                    printf((info.st_mode & S_IROTH) ? "r" : "-");
                    printf((info.st_mode & S_IWOTH) ? "w" : "-");
                    printf((info.st_mode & S_IXOTH) ? "x" : "-");
                    printf(" ");

                    printf("%3d ", (int)info.st_nlink);

                    printf("%8.8s ", (getpwuid(info.st_uid)->pw_name));
                    printf("%8.8s ", (getgrgid(info.st_gid)->gr_name));
                    
                    printf("%12lld ", (long long)info.st_size);
                    t = localtime(&info.st_mtime);

                    long int* c=(&info.st_mtime);
                    time_t seconds=time(0);
                    
                    strftime(date_modified, MAX_ARRAY_SIZE, nl_langinfo(D_T_FMT), t);
                    char month[4];
                    for (int h = 4; h < 7; h++)
                        month[h - 4] = date_modified[h];
                    month[3] = '\0';
                    char yr[5];
                    for (int h = 20; h < 24; h++)
                        yr[h - 20] = date_modified[h];
                    yr[4] = '\0';
                    //int result = decide(month, yr);
                    char datee[3];
                    for (int h = 8; h < 10; h++)
                        datee[h - 8] = date_modified[h];
                    datee[2] = '\0';
                    char samay[6];
                    for (int h = 11; h < 16; h++)
                        samay[h - 11] = date_modified[h];
                    samay[5] = '\0';
                    if (seconds-*c>six_mon) //m d y
                    {

                        printf(" %s %s %s %s\n", month, datee, yr, d->d_name);
                    }
                    else
                    {
                        printf(" %s %s %s %s\n", month, datee, samay, d->d_name);
                    }
                }
                closedir(dir);
                k++;
                // printf("\n");
            }
        }

        else if (j < 1)
        {
            getcwd(find_dir[0], MAX_ARRAY_SIZE);
            dir = opendir(find_dir[0]);

            //printf("total %ld\n",info.st_size);
            long long block = 0;
            while ((d = readdir(dir)) != NULL)
            {
                //struct stat info;
                if (a == 0 && (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || d->d_name[0]=='.'))
                    continue;

                stat(d->d_name, &info);
                block = block + info.st_blocks;
            }
            closedir(dir);
            printf("total %lld\n", block / 2);
            dir = opendir(find_dir[0]);
            while ((d = readdir(dir)) != NULL)
            {
                //struct stat info;
                if (a == 0 && (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0 || d->d_name[0]=='.'))
                    continue;

                stat(d->d_name, &info);

                printf((S_ISDIR(info.st_mode)) ? "d" : "-");
                printf((info.st_mode & S_IRUSR) ? "r" : "-");
                printf((info.st_mode & S_IWUSR) ? "w" : "-");
                printf((info.st_mode & S_IXUSR) ? "x" : "-");
                printf((info.st_mode & S_IRGRP) ? "r" : "-");
                printf((info.st_mode & S_IWGRP) ? "w" : "-");
                printf((info.st_mode & S_IXGRP) ? "x" : "-");
                printf((info.st_mode & S_IROTH) ? "r" : "-");
                printf((info.st_mode & S_IWOTH) ? "w" : "-");
                printf((info.st_mode & S_IXOTH) ? "x" : "-");
                printf(" ");

                printf("%3ld ", info.st_nlink);

                printf("%8.8s ", (getpwuid(info.st_uid)->pw_name));
                printf("%8.8s ", (getgrgid(info.st_gid)->gr_name));

                printf("%12ld ", info.st_size);
                t = localtime(&info.st_mtime);
                strftime(date_modified, MAX_ARRAY_SIZE, nl_langinfo(D_T_FMT), t);
                char month[4];
                for (int h = 4; h < 7; h++)
                    month[h - 4] = date_modified[h];
                month[3] = '\0';
                char yr[5];
                for (int h = 20; h < 24; h++)
                    yr[h - 20] = date_modified[h];
                yr[4] = '\0';
                //int result = decide(month, yr);
                char datee[3];
                for (int h = 8; h < 10; h++)
                    datee[h - 8] = date_modified[h];
                datee[2] = '\0';
                char samay[6];
                for (int h = 11; h < 16; h++)
                    samay[h - 11] = date_modified[h];
                samay[5] = '\0';
                long int* c=(&info.st_mtime);
                time_t seconds=time(0);
                if (seconds-*c>six_mon) //m d y
                {

                    printf(" %s %s %s %s\n", month, datee, yr, d->d_name);
                }
                else
                {
                    printf(" %s %s %s %s\n", month, datee, samay, d->d_name);
                }
            }
            closedir(dir);
        }
    }
    return;
}