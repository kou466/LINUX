#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s <디렉토리>\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0777) == -1) {
        printf("디렉토리를 생성할 수 없습니다.\n");
        return 1;
    }

    printf("디렉토리가 생성되었습니다.\n");

    return 0;
}

