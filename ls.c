#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void list_directory(const char *path, bool l_flag, bool a_flag, bool h_flag, bool R_flag);

void display_info(const char *path, const struct dirent *entry, bool h_flag);

int main(int argc, char *argv[])
{
    int opt;
    bool l_flag = false;
    bool a_flag = false;
    bool h_flag = false;
    bool R_flag = false;

    while ((opt = getopt(argc, argv, "lahR")) != -1)
    {
        switch (opt)
        {
        case 'l':
            l_flag = true;
            break;
        case 'a':
            a_flag = true;
            break;
        case 'h':
            h_flag = true;
            break;
        case 'R':
            R_flag = true;
            break;
        default:
            printf("Usage: %s [-l] [-a] [-h] [-R] [directory]\n", argv[0]);
            return 1;
        }
    }

    const char *path = ".";
    if (optind < argc)
    {
        path = argv[optind];
    }

    list_directory(path, l_flag, a_flag, h_flag, R_flag);
    return 0;
}

void list_directory(const char *path, bool l_flag, bool a_flag, bool h_flag, bool R_flag)
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    if ((dir = opendir(path)) == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && !a_flag)
        {
            continue;
        }

        if (l_flag)
        {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            stat(full_path, &file_stat);
            display_info(full_path, entry, h_flag);
        }
        else
        {
            printf("%s\n", entry->d_name);
        }

        if (R_flag && entry->d_type == DT_DIR)
        {
            char new_path[1024];
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                printf("\n%s:\n", new_path);
                list_directory(new_path, l_flag, a_flag, h_flag, R_flag);
            }
        }
    }

    closedir(dir);
}

void display_info(const char *path, const struct dirent *entry, bool h_flag)
{
    struct stat file_stat;
    stat(path, &file_stat);

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %ld", file_stat.st_nlink);

    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);

    if (h_flag)
    {
        float size = file_stat.st_size;
        const char *unit = "B";
        if (size > 1024)
        {
            size /= 1024;
            unit = "KB";
        }
        if (size > 1024)
        {
            size /= 1024;
            unit = "MB";
        }
        if (size > 1024)
        {
            size /= 1024;
            unit = "GB";
        }
        printf(" %6.2f %s", size, unit);
    }
    else
    {
        printf(" %6ld", file_stat.st_size);
    }

    char time_str[18];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&file_stat.st_mtime));
    printf(" %s", time_str);

    printf(" %s\n", entry->d_name);
}

