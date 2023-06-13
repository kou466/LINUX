#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "사용법: %s [파일1] [파일2]\n", argv[0]);
        return 1;
    }

    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "rb");
    fp2 = fopen(argv[2], "rb");

    if (!fp1 || !fp2)
    {
        perror("fopen");
        return 1;
    }

    int byte_pos = 0;
    bool files_match = true;
    while (true)
    {
        int char1 = fgetc(fp1);
        int char2 = fgetc(fp2);

        byte_pos++;

        if (char1 == EOF && char2 == EOF)
        {
            break;
        }

        if (char1 != char2)
        {
            files_match = false;
            printf("%s %s differ: byte %d\n", argv[1], argv[2], byte_pos);
            break;
        }
    }

    fclose(fp1);
    fclose(fp2);

    if (files_match)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
