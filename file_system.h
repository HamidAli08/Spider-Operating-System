#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_FILES 10
#define MAX_DIRS 10

// Structure for a File
typedef struct {
    char name[MAX_NAME_LENGTH];
} File;

// Structure for a Directory
typedef struct Directory {
    char name[MAX_NAME_LENGTH];
    struct Directory *parent;
    struct Directory *subdirs[MAX_DIRS];
    File files[MAX_FILES];
    int subdir_count;
    int file_count;
} Directory;

// Function prototypes
void initialize_file_system();
void create_directory(char *name);
void create_file(char *name);
void delete_file(char *name);
void change_directory(char *name);
void list_contents();
void handle_commands();
void mini_file_system();

#endif // FILE_SYSTEM_H
