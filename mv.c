#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("사용법: %s <소스파일> <대상파일>\n", argv[0]);
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        printf("파일을 이동 또는 이름을 변경할 수 없습니다.\n");
        return 1;
    }

    printf("파일이 이동되거나 이름이 변경되었습니다.\n");

    return 0;
}

