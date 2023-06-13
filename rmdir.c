#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s <디렉토리>\n", argv[0]);
        return 1;
    }

    if (rmdir(argv[1]) == -1) {
        printf("디렉토리를 삭제할 수 없습니다.\n");
        return 1;
    }

    printf("디렉토리가 삭제되었습니다.\n");

    return 0;
}

