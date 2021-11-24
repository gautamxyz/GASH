#ifndef def_h
#define def_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/wait.h>
#include<errno.h>
#include <dirent.h>
#include<grp.h>
#include<sys/stat.h>
#include<time.h>
#include <locale.h>
#include <langinfo.h>
#include <sys/utsname.h>

#define MAX_ARRAY_SIZE 2000
#define MAX_NO_COMMANDS 100
#define CLR_SCR printf("\e[1;1H\e[2J")   
#define six_mon 1.557e+7
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int bg;
int pid;
int fg;
int exiting;
char home_of_shell[MAX_ARRAY_SIZE];
int changed_dir;
int no_bg_processes;
char processes[100][MAX_ARRAY_SIZE];
int pro_ids[100];
char fg_name[MAX_ARRAY_SIZE];

char previous_dir[MAX_ARRAY_SIZE];
void display(char curr_dir[],char home_of_shell[]);
void execute(char buffer[][MAX_ARRAY_SIZE], int count);
void ls_command(char str[][MAX_ARRAY_SIZE],int no_args);

int bg_command(char str[][MAX_ARRAY_SIZE],int no_args);
int fg_command(char str[][MAX_ARRAY_SIZE],int no_args);
void pinfo_command(char str[][MAX_ARRAY_SIZE],int no_args);
void finish_bg();
void repeat(char A[][MAX_ARRAY_SIZE],int y);
void ls_for_file(char fil[],int l,int a);


int check_redirection(char *stri);
void cz();
void sig();
int parse_arg(char *t1,char **parts);
int check_piping(char * command);
void print_jobs(char str[][MAX_ARRAY_SIZE],int no_args);
void sig2(char str[][MAX_ARRAY_SIZE],int no_args);
void handle_fg(char str[][MAX_ARRAY_SIZE], int no_args);
void handle_bg(char str[][MAX_ARRAY_SIZE],int no_args);
void replay(char str[][MAX_ARRAY_SIZE],int no_args);
#endif