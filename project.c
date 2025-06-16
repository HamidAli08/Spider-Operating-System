#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "process_management.h"
#include "memory_management.h"
#include "file_system.h"
#include "scheduling_visualizer.h"
#include <unistd.h> // For sleep (on POSIX systems)
#ifdef _WIN32
#include <windows.h> // For Sleep (on Windows)
#endif

#define MAX_USERS 3
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH]; // In real-world, this should be hashed
} User;

User user_db[MAX_USERS];

int get_terminal_width() {
    const char *cols = getenv("COLUMNS");
    return (cols != NULL) ? atoi(cols) : 80; // Default to 80 if COLUMNS is not set
}

void print_centered(const char *str) {
    int term_width = get_terminal_width();
    int len = strlen(str);
    int padding = (term_width - len) / 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", str);
}

void display_splash_screen() { 
    printf("\033[H\033[J");
    print_centered(" /\\  .-''''-.  /\\ \n");
    print_centered(" //\\    ,,,    //\\ \n");
    print_centered("  |/\\| ,;;;;;, |/\\| \n");
    print_centered("  //\\;""""-;///\\ \n");
    print_centered("  //\\/   .   \\/ \\ \n");
    print_centered(" ( | ,-_| \\ | / |_-, |)\n");
    print_centered(" //`__\\.-.-.//__`\\ \n");
    print_centered(" // /.-(() ())-.\\ \\ \n");
    print_centered(" ( /|)   '---'   (|/ /)\n");
    print_centered("  ` (|           |) ` \n");
    print_centered( "  /)           (/ \n");
    print_centered( " SPIDER_OS_SIM \n");
    #ifdef _WIN32
        Sleep(3000); // Sleep for 3000 milliseconds on Windows
    #else
        sleep(3);    // Sleep for 3 seconds on POSIX systems
    #endif
}

void initialize_user_db() {
    strcpy(user_db[0].username, "admin");
    strcpy(user_db[0].password, "admin123");
    
    strcpy(user_db[1].username, "Syed_Hashir_Ali");
    strcpy(user_db[1].password, "hashir123");

    strcpy(user_db[2].username, "Hamid_Ali");
    strcpy(user_db[2].password, "ali123");
}

int authenticate_user(char *username, char *password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(user_db[i].username, username) == 0 &&
            strcmp(user_db[i].password, password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

int login() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    int attempts = 3;

    while (attempts > 0) {
        printf("\033[H\033[J"); // Clear the screen

        print_centered("===============================================");
        print_centered("          WELCOME TO THE SPIDER_OS_SIM LOGIN          ");
        print_centered("===============================================");
        print_centered("");
        print_centered("             Please enter your details           ");
        print_centered("");

        print_centered("\t ╔══════════════════════════════════════════════╗");
        printf("%*s", get_terminal_width() / 2 - 20, " ");
        printf("║ Username: ");
        scanf("%s", username);
        printf("%*s", get_terminal_width() / 2 - 20, " ");
        printf("║ Password: ");
        scanf("%s", password);
        print_centered("╚══════════════════════════════════════════════╝");

        if (authenticate_user(username, password)) {
            printf("\033[H\033[J"); // Clear the screen after successful login
            print_centered("===============================================");
            print_centered("           AUTHENTICATION SUCCESSFUL!           ");
            print_centered("===============================================");
            print_centered("");
            char welcome_msg[50];
            snprintf(welcome_msg, sizeof(welcome_msg), "Welcome, %s!", username);
            print_centered(welcome_msg);
            return 1; // Successful login
        } else {
            attempts--;
            printf("\033[H\033[J"); // Clear the screen for a fresh prompt
            print_centered("===============================================");
            print_centered("                INVALID CREDENTIALS             ");
            print_centered("===============================================");
            char attempts_left[50];
            snprintf(attempts_left, sizeof(attempts_left), "You have %d attempt(s) remaining.", attempts);
            print_centered(attempts_left);
        }
    }

    printf("\033[H\033[J"); // Clear the screen after too many failed attempts
    print_centered("===============================================");
    print_centered("           TOO MANY FAILED ATTEMPTS!            ");
    print_centered("                  ACCESS DENIED                 ");
    print_centered("===============================================");
    return 0; // Failed login
}

void perform_admin_action() {
    print_centered("You have admin privileges! Performing a sensitive action...\n");
}

// New function for shutdown behavior
void shutdown_system() {
    printf("\033[H\033[J"); // Clear the screen
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("               SHUTTING DOWN...                ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    print_centered("						   ");
    #ifdef _WIN32
        Sleep(3000); // 3 seconds on Windows
    #else
        sleep(3);    // 3 seconds on POSIX systems
    #endif
    printf("\033[H\033[J");
}

int main() {
    int choice;

    display_splash_screen();
    initialize_user_db();

    if (!login()) {
        return 0; // Exit if authentication fails
    }

    while (1) {
        print_centered("===============================================");
        print_centered("           SPIDER_OS_SIM - MAIN MENU                  ");
        print_centered("===============================================");
        print_centered("1. Process Management");
        print_centered("2. Memory Management");
        print_centered("3. File Management");
        print_centered("4. Scheduling Visualizer (Graphical Representation)");
        print_centered("5. Play Game");
        print_centered("6. Exit");
        print_centered("===============================================");
        print_centered("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                my_process();
                break;
            case 2:
                handle_memory_management();
                break;
            case 3:
                mini_file_system();
                break;
            case 4:
                run_scheduler();
                break;
            case 5:
                play_rock_paper_scissors();
                break;
            case 6:
                shutdown_system(); // Call the shutdown function
                return 0;
            default:
                print_centered("Invalid choice. Try again.");
        }
    }

    return 0;
}

