#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char** argv) {

    if (argc == 1)
    {
        while (1)
        {
            char** buffer = (char**)malloc(BUFFER_SIZE * sizeof(char*));
            scanf("%[^\n]%*c", buffer);
            printf("%s\n", buffer);
        }
    }

    else if (argc == 2)
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *fp;
            char buff[BUFFER_SIZE];
            fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                printf("cat: %s: No such file or directory\n", argv[i]);
                exit(1);
            }
            printf("\n");
            while (fgets(buff, BUFFER_SIZE, fp) != NULL)
            {
                printf("%s", buff);
            }
            fclose(fp);
        }
    }

    else if (argc == 3)
    {
        if (strcmp(argv[1], "-n") == 0)
        {
            int k = 1;
            for (int i = 2; i < argc; i++)
            {
                FILE *fp;
                char buff[BUFFER_SIZE];
                fp = fopen(argv[i], "r");
                if (fp == NULL)
                {
                    printf("cat: %s: No such file or directory\n", argv[i]);
                    exit(1);
                }
                printf("\n");
                while (fgets(buff, BUFFER_SIZE, fp) != NULL)
                {
                    printf("%d %s",k, buff);
                    k++;
                }
                fclose(fp);
            }
        }

        else if (strcmp(argv[1], "-E") == 0)
        {
            for (int i = 2; i < argc; i++)
        {
            FILE *fp;
            char buff[BUFFER_SIZE];
            fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                printf("cat: %s: No such file or directory\n", argv[i]);
                exit(1);
            }
            printf("\n");
            char ch = '$';

            while (fgets(buff, BUFFER_SIZE, fp) != NULL)
            {
                buff[strcspn(buff, "\n")] = 0;
                strncat(buff, &ch, 1);
                printf("%s\n", buff);
            }
            fclose(fp);
        }
        }
    }

    else
    {
        printf("cat: invalid option -- '%s'\n", argv[1]);
    }

    return 0;
}