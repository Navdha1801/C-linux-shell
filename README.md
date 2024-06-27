# Description
1. main.c file contains the conditions of different user defined commands and also codes to run background and foreground processes.Also handles other system defined commands.
2. checkint.c contains function which basically checks if the given token of string is an integer or not.I have used it to check for  erroneous commands.
3. count.c contains function which counts the occurance of a particular character in a string.
4. past.c contains function to execute the command of pastevents execute.
5. path.c contains function to print the relative path in prompt.
6. peek.c contains function to print files and their details according to the flag used.
7. proclore.c contains function to execute the proclore command.
8. seek.c contains function to implement the seek command according to the flags provided by user.
9. seekfile.c contains recursive function which searches for the name of file or folder as provided by user.
10. warp.c contains function to implement warp command.All flags are included accordingly.
11. activities.c contains functions to add, update the information,remove processes(spawned by shell) from the activities list(which is an array of struct which stores information of spawned processes).
12. neonate.c contains functions required to execute neonate command.
13. signal.c contains codes for interrupting processes through ctrl c and stopping a foreground process and pushing it to background.
# Assumptions
1. I am not handling piping through pastevents i.e., I am not storing piping arguments in pastevents.
