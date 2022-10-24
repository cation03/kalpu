- type "make" after cloning the repo and cding into it
- run ```./kalpesh```
- external commands supported:
    1. ls : lists all files not starting with .
        - ```-a``` : lists all files including those starting with .
        - ```-1``` : lists each file on newline

        - Corner Cases Defended
            1. if invalid option is passed into ls
            2. if too many arguments are passed into ls

    2. mkdir : creates a directory
        - ```-v``` : verbose - informs that a directory has been created
        - ```-p``` : creates parent directories as well

        - Corner Cases Defended
            1. if an operand is missing, e.g. filename after mkdir
            2. if a directory cannot be created because it already exists

    3. rm :
        - ```-i``` : prompts before removal
        - ```-v``` : informs after removal

        - Corner Cases Defended
            1. if the user tries to remove a file that does not exist
            2. if there is a missing operand
            3. if an invalid option is passed into rm


    4. cat :
        - ```-n``` :
        - ```-E``` :

        - Corner Cases Defended
            1. if the user tries to open a file or directory that doesn't exist
            2. if the user passes an invalid option


    5. date :
        - ```-u``` : time in gmt
        - ```-R``` : time in rfc 5322 format

        - Corner Cases Defended
            1. invalid option
            2. invalid command


- internal commands supported:
    1. cd :
        - ```-``` : goes to previous working directory
        - ```-P``` : symbolic link components shall be resolved before dot-dot components are processed
        - ```-L``` : symbolic link components shall not be resolved before dot-dot components are processed
        - ```--help```: prints help

        - Corner Cases Defended
            1. passes an invalid option
            2. passes an invalid number of arguments


    2. pwd :
        - ```-L``` : follow symlinks
        - ```-P``` : dont follow symlinks

        - Corner Cases Defended
            1. cannot read current directory
            2. invalid option


    3. echo :
        - ```--help``` : print help
        - ```-n``` : removes newline

        - Corner Cases Defended
            1. invalid option
            2. invalid command

## Use of fork() and exec()

- used fork() and exec() calls
- fork() creates a new process by copying the current running one
- exec() replaces the new, child process with the required process


## Use of pthread_create and system in commands involving "&t"

- pthread_create() creates a new thread to run the command
- the command needs to be of the form "command&t -option"
- for example, "ls&t -1"