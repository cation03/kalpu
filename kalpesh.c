#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define BUFFER_SIZE 4096

// function to reverse string

void reverseString(char* reverse)
{
    int len = strlen(reverse);
    for (int i = 0; i < len/2; i++)
    {
        char temp = reverse[i];
        reverse[i] = reverse[len-i-1];
        reverse[len-i-1] = temp;
    }
}

void getPwd(size_t buffSize)
{
    char *pwd = (char*)malloc(buffSize*sizeof(char));
    if (getcwd(pwd, buffSize) != NULL)
    {
        printf("%s\n", pwd);
    }
    else
    {
        perror("getcwd() error");
    }
}

int main()
{
	char* cmds[5] = {"rm", "mkdir", "ls", "cat", "date"};
	char* rPs[5] = {realpath("rm", NULL), realpath("mkdir", NULL), realpath("ls", NULL), realpath("cat", NULL), realpath("date", NULL)};

	size_t buffSize = BUFFER_SIZE;
    char *buffer;
    buffer = (char*)malloc(buffSize*sizeof(char));

    while (1)
    {
        printf("kalpesh@kalpesh:~$ ");
    	scanf("%[^\n]%*c", buffer);
        char *token = strtok(buffer, " ");

        // echo cmd
        if (strcmp(token, "echo") == 0)
        {
            token = strtok(NULL, " ");

            if (strcmp(token, "--help") == 0)
            {
                printf("echo - display a line of text.\n");
                printf("echo [SHORT-OPTION]... [STRING]...echo LONG-OPTION\n");
                printf("DESCRIPTION\n");
                printf("Echo the STRING(s) to standard output.\n");
                printf("       -n     do not output the trailing newline\n");
                printf("       -e     enable interpretation of backslash escapes\n");
                printf("       -E     disable interpretation of backslash escapes (default)\n");
                printf("       --help display this help and exit\n");
                printf("--version     output version information and exit\n");
                printf("       If -e is in effect, the following sequences are recognized:\n");
                printf("       \\     backslash\n");
                printf("       \\a     alert (BEL)\n");
                printf("       \\b     backspace\n");
                printf("       \\c     produce no further output\n");
                printf("        \\e     escape\n");
                printf("        \\F    form feed\n");
                printf("        \\n     new line\n");
                printf("        \r      carriage return\n");
                printf("        \\t     horizontal tab\n");
                printf("        \\v     vertical tab\n");
                printf("        \\0NNN  byte with octal value NNN (1 to 3 digits)\n");
                printf("        \\xHH   byte with hexadecimal value HH (1 to 2 digits)\n");
                printf("       NOTE: your shell may have its own version of echo, which usually supersedes the version described here.  Please refer to your shell documentation for details about the options it supports.\n");
                printf("AUTHOR\n");
                printf("Written by Brian Fox and Chet Ramey.\n");
            }

            else if (strcmp(token, "-n") == 0)
            {
                printf("%s", token);
                token[strcspn(token, "\n")] = 0;
                token = strtok(NULL, " ");

                while (token != NULL)
                {
                    token[strcspn(token, "\n")] = 0;
                    printf("%s ", token);
                    token = strtok(NULL, " ");
                }
            }

            else if ((strcmp(token, "-n") != 0) && (strcmp(token, "--help") != 0))
            {
                while (token != NULL)
                {
                    printf("%s ", token);
                    token = strtok(NULL, " ");
                }
                printf("\n");
            }

            else
            {
                printf("echo: invalid option -- '%s'\n", token);
                printf("Try 'echo --help' for more information.\n");
            }
        }

        // pwd cmd
        else if (strcmp(token, "pwd") == 0)
        {
		int flag = 0;
            char *pwd = (char*)malloc(buffSize*sizeof(char));
            char* newthing = (char*)malloc(buffSize*sizeof(char));
            strcpy(newthing, token);
            token = strtok(NULL, " ");

            if ((strcmp(newthing, "-L") == 0))
            {
            printf("%s\n", getenv("PWD"));
            newthing = strtok(NULL, " ");
            flag = 1;
            }
            else if ((strcmp(newthing, "-P") == 0))
            {
            char *pwd1 = (char*)malloc(buffSize*sizeof(char));
            newthing = strtok(NULL, " ");
            getcwd(pwd1, 4096);
            printf("%s", pwd1);
            printf("\n");
            flag = 1;
            }

	    else if (flag == 0)
            {
                getPwd(buffSize);
            }

            else
            {
                perror("getcwd() error");
            }
        }

        // cd cmd
        else if (strcmp(token, "cd") == 0)
        {
            token = strtok(NULL, " ");
            int flag = 0;
            if (token == NULL)
            {
                chdir(getenv("HOME"));
            }
            else if (strcmp(token, "-") == 0)
            {
                chdir(getenv("OLDPWD"));
                // printf("%s\n", getcwd(buffer, buffSize));
                size_t bufferSize = 4096;
                printf("%s\n", getPwd(bufferSize));
            }

            else if (strcmp(token, "-P") == 0)
            {
                token = strtok(NULL, " ");
                if (token == NULL)
                {
                    chdir(getenv("HOME"));
                }
                else
                {
                    chdir(token);
                }
            }

            else if (strcmp(token, "-L") == 0)
            {
                token = strtok(NULL, " ");
                if (token == NULL)
                {
                    chdir(getenv("HOME"));
                }
                else
                {
                    chdir(token);
                }
            }

            else if (strcmp(token, "--help") == 0)
            {
                printf("cd: cd [-L|[-P [-e]] [-@]] [dir]\n");
                printf("Change the shell");
                printf("working directory.\n");
                printf("  -L\tforce symbolic links to be followed: resolve symbolic\n");
                printf("  \tlinks in DIR after processing instances of `..'\n");
                printf("  -P\tuse the physical directory structure without following\n");
                printf("  \tsymbolic links: resolve symbolic links in DIR before\n");
                printf("  \tprocessing instances of `..'\n");
                printf("  -e\tif the -P option is supplied, and the current working\n");
                printf("  \tdirectory cannot be determined successfully, exit with\n");
                printf("  \ta non-zero status\n");
                printf("  -@ on systems that support it, present a file with extended\n");
                printf("  \tattributes as a directory containing the file attributes\n");
                printf("  \t\n");
                printf("The default is to follow symbolic links, as if `-L' were specified.\n");
                printf("The variable `CDPATH' defines the search path for the directory\n");
                printf("containing DIR.  Alternative directory names in CDPATH are\n");
                printf("separated by a colon (:).  A null directory name is the same as\n");
                printf("the current directory.  If DIR begins with a slash (/), then\n");
                printf("CDPATH is not used.\n");
                printf("If the directory is not found, and the shell option `cdable_vars'\n");
                printf("is set, the word is assumed to be  a variable name.  If that\n");
                printf("variable has a value, its value is used for DIR.\n");
                printf("Exit Status:\n");
                printf("Returns 0 if the directory is changed, and if $PWD is set successfully when\n");
                printf("the -P option is supplied; non-zero otherwise.\n");
            }

            else
            {
                // errors for cd
                if (chdir(token) != 0)
                {
                    perror("chdir() error");
                }
                else
                {
                    flag = 1;
                }
            }
        }

        // exit cmd
        else if (strcmp(token, "exit") == 0)
        {
            exit(0);
        }

        // &t handling
        else
        {
            int useThreading = 0;
            reverseString(token);

            if (token[0] == 't' && token[1] == '&')
            {
                useThreading = 1;
            }

            reverseString(token);

            if (useThreading)
            {
                int len = strlen(token);
                token[len-2] = '\0';
            }

            char cmdGiven[10];
            int flag = 0;
            int idx = 0;
            for (int i = 0; i < 5; i++)
            {
                if (strcmp(token, cmds[i]) == 0)
                {
                    strcpy(cmdGiven, cmds[i]);
                    flag = 1;
                    idx = i;
                    break;
                }
            }

            if (flag == 0)
            {
                printf("command not found\n");
                continue;
            }

            if (useThreading)
            {
                char* finalBuffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
                strcpy(finalBuffer, rPs[idx]);
                strcat(finalBuffer, " ");

                while (1)
                {
                    token = strtok(NULL, " ");
                    if (token == NULL)
                    {
                        break;
                    }
                    strcat(finalBuffer, token);
                    strcat(finalBuffer, " ");
                }

                // THREADING CODE
                // printf("finaluffer = %s\n", finalBuffer);
                pthread_t id;
                int p = pthread_create(&id, NULL, system, finalBuffer);

                if (p != 0)
                {
                    perror("pthread_create() error");
                    exit(EXIT_FAILURE);
                }

                else
                {
                    pthread_join(id, NULL);
                }
            }

            else {
                // FORKING CODE

                char** arr = (char**)malloc(BUFFER_SIZE * sizeof(char*));
                int k = 0;
                while (token != NULL)
                {
                    arr[k] = token;
                    token = strtok(NULL, " ");
                    k++;
                }

                pid_t id = fork();

                if (id == -1)
                {
                    perror("fork() error");
                    exit(EXIT_FAILURE);
                }

                else if (id == 0)
                {
                    int returnVal = execv(rPs[idx], arr);
                    printf("%s", rPs[idx]);

                    if (returnVal == -1)
                    {
                        perror("execv() error");
                        exit(1);
                    }
                }

                else
                {
                    int waitStatus = 0;
                    int w = waitpid(id, &waitStatus, 0);

                    if (w == -1)
                    {
                        perror("waitpid() error");
                    }
                }
            }
        }
    }
    return 0;
}