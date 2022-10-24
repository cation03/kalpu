#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("mkdir: missing operand\n");
    }

    else
    {
        if (argc == 2)
        {
            struct stat st = {0};
            if (stat(argv[1], &st) == -1)
            {
                mode_t mode = 0777;
                int confirm = mkdir(argv[1], mode);

                if (confirm != 0)
                {
                    printf("mkdir: cannot create directory '%s'\n", argv[1]);
                }

            }
        }

        else if (strcmp(argv[1], "-v") == 0)
        {
            for (int i = 2; i < argc; i++)
            {
                struct stat st = {0};
                if (stat(argv[i], &st) == -1)
                {
                    mode_t mode = 0777;
                    int confirm = mkdir(argv[i], mode);

                    if (confirm != 0)
                    {
                        printf("mkdir: cannot create directory '%s'\n", argv[i]);
                    }

                    else if (confirm == 0)
                    {
                        printf("mkdir: created directory '%s'\n", argv[i]);
                    }
                }
            }
        }

        else if (strcmp(argv[1], "-p") == 0)
        {
            for (int i = 2; i < argc; i++)
            {
                size_t buffSize = BUFFER_SIZE;
                char *buffer;
                buffer = (char*)malloc(buffSize*sizeof(char));
                strcpy(buffer, argv[i]);
                int k = 0;
                char *token = strtok(buffer, "/");
                char** arr = (char**)malloc(BUFFER_SIZE * sizeof(char*));

                while (token != NULL)
                {
                    arr[k] = token;
                    token = strtok(NULL, "/");
                    k++;
                }

                for (int i = 0; i < k; i++)
                {
                    struct stat st = {0};
                    if (stat(arr[i], &st) == -1)
                    {
                        mode_t mode = 0777;
                        int confirm = mkdir(arr[i], mode);

                        if (confirm != 0)
                        {
                            printf("mkdir: cannot create directory '%s'\n", arr[i]);
                        }
                    }
		    chdir(arr[i]);
                }
            }
        }

        else if (argc > 2)
        {
            for (int i = 1; i < argc; i++)
            {
                struct stat st = {0};
                if (stat(argv[i], &st) == -1)
                {
                    mode_t mode = 0777;
                    int confirm = mkdir(argv[i], mode);

                    if (confirm != 0)
                    {
                        perror("mkdir");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    return 0;
}
