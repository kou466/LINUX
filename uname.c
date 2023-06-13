#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;
    int opt_s = 0, opt_r = 0, opt_v = 0, opt_m = 0, opt_p = 0, opt_o = 0;
    int no_option_passed = 1;
    struct utsname un;

    while ((opt = getopt(argc, argv, "srvmpo")) != -1) {
        no_option_passed = 0;
        
        switch (opt) {
            case 's':
                opt_s = 1;
                break;
            case 'r':
                opt_r = 1;
                break;
            case 'v':
                opt_v = 1;
                break;
            case 'm':
                opt_m = 1;
                break;
            case 'p':
                opt_p = 1;
                break;
            case 'o':
                opt_o = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] [-r] [-v] [-m] [-p] [-o]\n", argv[0]);
                return 1;
        }
    }

    if (uname(&un) == -1) {
        perror("uname");
        return 1;
    }

    if (opt_s || no_option_passed) {
        printf("%s\n", un.sysname);
    }

    if (opt_r) {
        printf("%s\n", un.release);
    }

    if (opt_v) {
        printf("%s\n", un.version);
    }

    if (opt_m) {
        printf("%s\n", un.machine);
    }

    if (opt_p) {
        printf("%s\n", un.machine);
    }

    if (opt_o) {
        printf("GNU/Linux\n");
    }

    return 0;
}
