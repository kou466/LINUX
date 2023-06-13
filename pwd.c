#include <stdio.h>
#include <unistd.h>

int main() {
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("현재 작업 중인 디렉토리: %s\n", cwd);
	} else {
		printf("디렉토리 경로를 가져올 수 없습니다.\n");
		return 1;
	}

	return 0;
}
