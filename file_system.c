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

Directory *root, *current;

// Function to initialize the file system
void initialize_file_system() {
    root = (Directory *)malloc(sizeof(Directory));
    strcpy(root->name, "root");
    root->parent = NULL;
    root->subdir_count = 0;
    root->file_count = 0;
    current = root;
}

// Function to create a directory
void create_directory(char *name) {
    if (current->subdir_count >= MAX_DIRS) {
        printf("Error: Maximum directory limit reached.\n");
        return;
    }
    Directory *new_dir = (Directory *)malloc(sizeof(Directory));
    strcpy(new_dir->name, name);
    new_dir->parent = current;
    new_dir->subdir_count = 0;
    new_dir->file_count = 0;

    current->subdirs[current->subdir_count++] = new_dir;
    printf("Directory '%s' created.\n", name);
}

// Function to create a file
void create_file(char *name) {
    if (current->file_count >= MAX_FILES) {
        printf("Error: Maximum file limit reached.\n");
        return;
    }
    strcpy(current->files[current->file_count++].name, name);
    printf("File '%s' created.\n", name);
}

// Function to delete a file
void delete_file(char *name) {
    for (int i = 0; i < current->file_count; i++) {
        if (strcmp(current->files[i].name, name) == 0) {
            for (int j = i; j < current->file_count - 1; j++) {
                current->files[j] = current->files[j + 1];
            }
            current->file_count--;
            printf("File '%s' deleted.\n", name);
            return;
        }
    }
    printf("Error: File '%s' not found.\n", name);
}

// Function to change directory
void change_directory(char *name) {
    if (strcmp(name, "..") == 0) {
        if (current->parent != NULL) {
            current = current->parent;
            printf("Moved to directory '%s'.\n", current->name);
        } else {
            printf("Error: Already in the root directory.\n");
        }
        return;
    }
    for (int i = 0; i < current->subdir_count; i++) {
        if (strcmp(current->subdirs[i]->name, name) == 0) {
            current = current->subdirs[i];
            printf("Moved to directory '%s'.\n", current->name);
            return;
        }
    }
    printf("Error: Directory '%s' not found.\n", name);
}

// Function to list contents of the current directory
void list_contents() {
    printf("\nContents of '%s':\n", current->name);
    printf("Directories:\n");
    for (int i = 0; i < current->subdir_count; i++) {
        printf("  [DIR] %s\n", current->subdirs[i]->name);
    }
    printf("Files:\n");
    for (int i = 0; i < current->file_count; i++) {
        printf("  [FILE] %s\n", current->files[i].name);
    }
}

// Function to handle user commands
void handle_commands() {
    char command[50], name[MAX_NAME_LENGTH];

    while (1) {
        printf("\n[%s] > ", current->name);
        scanf("%s", command);

        if (strcmp(command, "mkdir") == 0) {
            scanf("%s", name);
            create_directory(name);
        } else if (strcmp(command, "touch") == 0) {
            scanf("%s", name);
            create_file(name);
        } else if (strcmp(command, "rm") == 0) {
            scanf("%s", name);
            delete_file(name);
        } else if (strcmp(command, "cd") == 0) {
            scanf("%s", name);
            change_directory(name);
        } else if (strcmp(command, "ls") == 0) {
            list_contents();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting file system.\n");
            break;
        } else {
            printf("Error: Unknown command '%s'.\n", command);
        }
    }
}

void mini_file_system() {
    initialize_file_system();
    handle_commands(); // Call the function to handle user commands
}
