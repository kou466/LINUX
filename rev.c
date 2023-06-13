#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str)
{
    size_t len = strlen(str);
    char temp;
    for (size_t i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *file;

    if (argc == 1)
    {
        file = stdin;
    }
    else
    {
        file = fopen(argv[1], "r");
        if (!file)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }

    // 파일의 각 줄 뒤집기
    while ((read = getline(&line, &len, file)) != -1)
    {
        reverse_string(line);
        printf("%s", line);
    }

    fclose(file);
    free(line);
    exit(EXIT_SUCCESS);
}