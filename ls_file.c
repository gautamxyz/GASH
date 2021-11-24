#include "shell.h"
void ls_for_file(char fil[], int l, int a)
{
    if (l == 0)
    {
        printf("%s\n\n", fil);
        return;
    }
    else
    {
        struct stat info;
        char date_modified[MAX_ARRAY_SIZE];
        struct tm *t;
        char curr[MAX_ARRAY_SIZE];
        getcwd(curr, MAX_ARRAY_SIZE);
        strcat(curr, "/");
        strcat(curr, fil);
        stat(curr, &info);
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
        strftime(date_modified, MAX_ARRAY_SIZE, nl_langinfo(D_T_FMT), t);
        char month[4];
        for (int h = 4; h < 7; h++)
            month[h - 4] = date_modified[h];
        month[3] = '\0';
        char yr[5];
        for (int h = 20; h < 24; h++)
            yr[h - 20] = date_modified[h];
        yr[4] = '\0';
        // int result = decide(month, yr);
        char datee[3];
        for (int h = 8; h < 10; h++)
            datee[h - 8] = date_modified[h];
        datee[2] = '\0';
        char samay[6];
        for (int h = 11; h < 16; h++)
            samay[h - 11] = date_modified[h];
        samay[5] = '\0';
        long int *c = (&info.st_mtime);
        time_t seconds = time(0);
        if (seconds-*c>six_mon) //m d y
        {

            printf(" %s %s %s %s\n\n", month, datee, yr, fil);
        }
        else
        {
            printf(" %s %s %s %s\n\n", month, datee, samay, fil);
        }
        return;
    }
}