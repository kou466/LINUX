#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <signal num> <PID>\n", argv[0]);
        return 1;
    }

    int signal_number = atoi(argv[1]);
    pid_t process_id = (pid_t)atoi(argv[2]);

    if (kill(process_id, signal_number) == -1) {
        perror("kill");
        return 1;
    }
    return 0;
}
