#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void removeFile(char *path)
{
    int confirm = remove(path);
    if (confirm != 0)
    {
        printf("rm: cannot remove '%s': No such file or directory\n", path);
    }
    exit(1);
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("rm: missing operand\n");
    }

    else if (argc == 3)
    {
        if (strcmp(argv[1], "-i") == 0)
        {
            for (int i = 2; i < argc; i++)
            {
                printf("rm: remove regular file '%s'?\n", argv[i]);
                char c[10];
                scanf("%s", &c);
                if (strcmp(c, "y") == 0)
                {
                    removeFile(argv[i]);
                }
            }
            exit(1);
        }

        else if (strcmp(argv[1], "-v") == 0)
        {
            for (int i = 2; i < argc; i++)
            {
                printf("removed '%s'\n", argv[i]);
                removeFile(argv[i]);
            }
            exit(1);
            
        }


        else
        {
            printf("rm: invalid option -- '%s'\n", argv[1]);
        }
    }

    else if (argc == 2)
    {
        for (int i = 1; i < argc; i++)
        {
            removeFile(argv[i]);
        }
    }

    exit(1);
    return 0;
}