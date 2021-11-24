# GAutam's SHell (GASH)
This shell written in C covers the implementation of all inbuilt shell commands, handles piping and redirection and also implements some additional commands. In case of wrong syntax/invalid commands appropriate error message is printed on the console.
## How to use?
Type `make` on your terminal. This will generate the executable `gash` file. Run it by giving the command `./gash`.

## Functions
+ `cd command` - changes directory to path given. If no path given it goes to home directory of the shell.
+ ` pwd `- diplays present working directory
+ `echo` - used to print on shell
+ `ls`  - list the files of given directory. Has flags -l(which lists details of all files in that directory such as permissions,memory,last date of modification) and -a.
+ `pinfo [pid]`   -prints information (pid,process status,memory,executable path) of a process
+ `clear`     - clears the console
+ `exit`  - exits the shell
+ `repeat [n] [command]`   -responsible for executing the given instruction `n` times
+ A background process can be run by putting `&` at the end.
  
+ handles redirection(<,>,>>) and piping (|)
+ `jobs`  - prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
their job number (a sequential number assigned by gash), process ID and their state, which can either be running​ or ​stopped​. It can take the flags -r(running),-s(stopped).
+ `sig [job_number] [signal]`  - gives the signal to job with the given job number.
+ `fg [job_number]` - brings a background job specified by the given job_number to foreground.
+ `bg [job_number]` - Changes the state of a stopped background job to running (in the background)
+ handles the following signals:
    - `ctrl+c` : interrupts any currently running foreground job, by sending it the ​SIGINT​ signal
    - `ctrl+d` : closes the program `gash`.
    - `ctrl+z `: pushes any currently running foreground job into the background, and change its state from running to stopped
+ `replay -command <command> -interval <interval> -period <period>` : executes the given command after every fixed time interval for given period.
+ All other commands are handled through execvp 


## Files
+ main.c - contains the while loop, takes input & parses it, also handles ctrl+c/z/d signals
+ execute.c - parses each command and identifies which command is to be executed. Also contains code for `cd,echo,pwd,repeat` commands.
+ pinfo.c - to print information of a process
+ bg.c - handles execution of background processes
+ ls.c - handles ls function along with its flags (-a,-l,-la,-al,-a -l).
+ ls_file.c - handles ls command for files
+ display.c - used to display the prompt
+ replay.c - handles replay command
+ sig2.c - handles bg,fg and sig command
+ jobs.c - handles jobs command
+ piping.c - handles piping
+ redirection.c - handles redirection
+ shell.h - contains the list of functions, global variables and #defines.