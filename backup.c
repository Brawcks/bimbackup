
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "backup.h"

#define NORMAL_COLOR "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

int main(int argc, char *argv[])
{
    double time_spent = 0.0;
    clock_t begin = clock();

    printf("%sStarting backup\n", NORMAL_COLOR);

    list_dir_content(argv[1]);

    printf("%s\n", NORMAL_COLOR);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
}

void open_file(struct dirent *dir, char *path) {
    FILE *file = NULL;
    char filepath[512];
    sprintf(filepath, "%s/%s", path, dir->d_name);

    // printf("%s\n", dir->d_name);
    // printf("%s\n", path);
    // printf("%s\n", filepath);

    file = fopen(filepath, "r+");

    if (file != NULL)
    {
        printf("File open : %s\n", filepath);

    } else {
        printf("Failed opening file");
    }
    
    // printf("%s%s\n", GREEN, path);
    // printf("%s%s\n", GREEN, dir->d_name);
}

void list_dir_content(char *path)
{
    DIR *d = opendir(path); // open the path
    char var[] = "";

    if (d == NULL)
        return;                        // if was not able return
    struct dirent *dir;                // for the directory entries
    while ((dir = readdir(d)) != NULL) // if we were able to read somehting from the directory
    {
        // If file
        if (dir->d_type != DT_DIR) {
            // printf("%s%s\n", BLUE, dir->d_name);
            // printf("%s%s\n", BLUE, path);
            open_file(dir, path);
        }

        // If dir
        else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
        {
            // printf("%s%s\n", GREEN, dir->d_name);
            char d_path[512];
            sprintf(d_path, "%s/%s", path, dir->d_name);
            // printf("%s\n", d_path);
            list_dir_content(d_path); // recall with the new path
        }
    }
    closedir(d); // finally close the directory
}
