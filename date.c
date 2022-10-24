#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        char buffer[BUFFER_SIZE];
        time_t t;
        time(&t);
        strftime(buffer, BUFFER_SIZE, "%a %b %d %H:%M:%S %Z %Y", localtime(&t));
        printf("%s\n", buffer);
    }

    else if (argc == 2)
    {
        if (strcmp(argv[1], "-u") == 0)
        {
            char buffer[BUFFER_SIZE];
            time_t t;
            time(&t);
            strftime(buffer, BUFFER_SIZE, "%a %b %d %H:%M:%S %Z %Y", gmtime(&t));
            printf("%s\n", buffer);
        }

        else if (strcmp(argv[1], "-R") == 0)
        {
            char buffer[BUFFER_SIZE];
            time_t t;
            time(&t);
            strftime(buffer, BUFFER_SIZE, "%a, %d %b %Y %H:%M:%S %z", localtime(&t));
            printf("%s\n", buffer);
        }
        else
        {
            printf("date: invalid option -- '%s'\n", argv[1]);
        }
    }

    else
    {
        printf("command not found\n");
    }

    return 0;
}