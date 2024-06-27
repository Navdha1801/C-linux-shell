# Description
1. First run the makefile.Run the command make and then ./myprogram.You will enter into the c shell.

2. "warp" command helps in changing the directory that the shell is currently in.It also prints the full path of working directory after changing.Here home directory is the c-linux-shell.“.”, “..”, “~”, and “-” flags are implemented in warp. ~ represents the home directory of shell.It supports both relative and absolute paths.If no argument is present, then warp into the home directory.If more than one argument is present,warp executes sequentially with all of them being the argument one by one.

3. "peek" command lists all the files and directories in the specified directories in lexicographic order (default peek does not show hidden files).It also supports -a and -l flags.
    -l : displays extra information
    -a : displays all files, including hidden files
 It supports “.”, “..”, “~”, and “-” symbols and both relative and absolute paths.Specific color coding is used to differentiate between file names, directories and executables in the output [green for executables, white for files and blue for directories].

4. "pastevents" command stores (and output) the 15 most recent command statements given as input to the shell based on some constraints. It overwrites the oldest commands if more than the set number (15) of commands are entered.Pastevents does not store a command if it is the exactly same as the previously entered command.It stores all statements except commands that include pastevents or pastevents purge.

5. "Pastevents purge" clears all the pastevents currently stored.It is not stored in pastevents.

6. The “;” command can be used to give multiple commands at the same time.

7. Shell executes other system commands present in Bash as well like emacs, gedit etc.It is  possible in both foreground and background processes.
Foreground process-Time taken by the foreground process and the name of the process is printed in the next prompt if process takes > 2 seconds to run.
Background process-Any command invoked with “&” is treated as a background command.Shell will keep taking other user commands. Whenever a new background process is started, print the PID of the newly created background process on your shell also.Multiple background processes can also run.Whenever background process finishes, display message to user.It prints process name along with pid when background process ends. Also mentions if the process ended normally or abnormally.

8. "proclore" is used to obtain information regarding a process. If an argument is missing, print the information of your shell.
Information printed :
  1.  pid
  2.  Process Status (R/R+/S/S+/Z)
  3.  Process group
  4.  Virtual Memory
  5.  Executable path of process
  Process states :

   1.  R/R+ : Running
   2. S/S+ : Sleeping in an interruptible wait
  "+" indicates foreground process.

9. "seek" command looks for a file/directory in the specified target directory (or current if no directory is specified). It returns a list of relative paths (from target directory) of all matching files/directories (files in green and directories in blue) separated with a newline character.

  Flags :

   1. -d : Only look for directories (ignore files even if name matches)
   2. -f : Only look for files (ignore directories even if name matches)
   3. -e : This flag is effective only when a single file or a single directory with the name is found. If only one file (and no directories) is found, then print it’s output. If only one directory (and no files) is found, then change current working directory to it. Otherwise, the flag has no effect. This flag should work with -d and -f flags. If -e flag is enabled but the directory does not have access permission (execute) or file does not have read permission, then output “Missing permissions for task!”

 Print “No match found!” in case no matching files/directories is found. Note that -d and -f flag can’t be used at the same time return error message “Invalid flags!”.

 A call to this command will always be in the format :

                                   seek <flags> <search> <target_directory>

10. I/O redirection-
I/O Redirection is when you change the default input/output (which is the terminal) to another file. This file can be used to read input into a program or to capture the output of a program. This specification works for all commands - user defined as well as system commands defined in bash. Shell supports >, <, » (<  works with both > and »).
  1. > : Outputs to the filename following “>”.
  2. >> : Similar to “>” but appends instead of overwriting if the file already exists.
  3. < : Reads input from the filename following “<”.
An error message “No such input file found!” should be displayed if the input file does not exist.
The output file should be created (with permissions 0644) if it does not already exist in both > and ».
In case the output file already exists, it should be overwritten in case of > and appended to in case of ».

11. "Pipes" are used to pass information between commands. It takes the output from command on left and passes it as standard input to the command on right.Shell supports any number of pipes. This specification works for all commands - user defined as well as system commands defined in bash.Return error “Invalid use of pipe”, if there is nothing to the left or to the right of a pipe.Run all the commands sequentially from left to right if pipes are present.

12. Redirection along with pipes-
 Shell is  able to run I/O redirection along with pipes.

13. "activities" print a list of all the processes currently running that were spawned by your shell in lexicographic order. This list contains the following information about all processes.
Format of an entry is : [pid] : [command name] - [State]

14. "ping" command send signals to processes. Take the pid of a process and send a signal to it which corresponds to the signal number (which is provided as an argument). Print error “No such process found”, if process with given pid does not exist.Take signal number’s modulo with 32 before checking which signal it belongs to.
Ctrl - C - Interrupt any currently running foreground process by sending it the SIGINT signal. It has no effect if no foreground process is currently running.
Ctrl - D - Log out of your shell (after killing all processes) while having no effect on the actual terminal.
Ctrl - Z - Push the (if any) running foreground process to the background and change it’s state from “Running” to “Stopped”. It has no effect on the shell if no foreground process is running.
* if any process is stopped permanently(meaning it is completed),then activities will show Stoppedf.Stopped means process is stopped temporary.

15. "fg" <pid> - Brings the running or stopped background process with corresponding pid to foreground, handing it the control of terminal. Print “No such process found”, if no process with given pid exists.

16. "bg" <pid> - Changes the state of a stopped background process to running (in the background). If a process with given pid does not exist, print “No such process found” to the terminal.

17. "neonate -n [time_arg]" - The command prints the Process-ID of the most recently created process on the system (you are not allowed to use system programs), this pid will be printed every [time_arg] seconds until the key ‘x’ is pressed.

18. "iMan"- iMan fetches man pages from the internet using sockets and outputs it to the terminal (stdout).



