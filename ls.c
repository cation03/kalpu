#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

void _ls(char *path, char* flag)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(flag, "-a") == 0)
            {
                printf("%s   ", ent->d_name);
            }

            else if (strcmp(flag, "-1") == 0)
            {
                if (ent->d_name[0] != '.')
                {
                    printf("%s\n", ent->d_name);
                }
            }

            else if (strcmp(flag, "0") == 0)
            {
                if (ent->d_name[0] != '.')
                {
                    printf("%s   ", ent->d_name);
                }
            }

            else
            {
                printf("ls: invalid option -- '%s'\n", flag);
            }
        }
        printf("\n");
        free(ent);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("ls: cannot access '%s': No such file or directory\n", path);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        _ls(".", "0");
    }

    else if (argc == 2)
    {
        if (strcmp(argv[1], "-a") == 0)
        {
            _ls(".", argv[1]);
        }

        else if (strcmp(argv[1], "-1") == 0)
        {
            _ls(".", argv[1]);
        }
    }

    else
    {
        printf("Too many arguments\n");
    }
    return 0;
}