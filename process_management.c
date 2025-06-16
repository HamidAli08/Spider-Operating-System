#define MAX_PROCESSES 10
#define TIME_QUANTUM 2
#define LOG_FILE "process_logs.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process_management.h"

// Define global variables in the source file
Process process_table[MAX_PROCESSES];

// Definitions of functions (unchanged from your original implementation)
void log_event(const char *event) {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        printf("Error: Unable to open log file.\n");
        return;
    }
    fprintf(log_file, "%s\n", event);
    fclose(log_file);
}

void create_process(char *name, int priority, int burst_time) {
    if (process_count >= MAX_PROCESSES) {
        printf("Error: Maximum process limit reached.\n");
        return;
    }
    process_table[process_count].pid = process_count + 1;
    strcpy(process_table[process_count].name, name);
    strcpy(process_table[process_count].state, "Waiting");
    process_table[process_count].priority = priority;
    process_table[process_count].burst_time = burst_time;

    char event[100];
    snprintf(event, sizeof(event), "Created Process: PID=%d, Name=%s, Priority=%d, Burst Time=%d",
             process_table[process_count].pid, name, priority, burst_time);
    log_event(event);

    printf("%s\n", event);
    process_count++;
}


// List all processes
void list_processes() {
    printf("PID\tName\t\tState\t\tPriority\tBurst Time\n");
    for (int i = 0; i < process_count; i++) {
        printf("%d\t%s\t\t%s\t\t%d\t\t%d\n",
               process_table[i].pid, process_table[i].name,
               process_table[i].state, process_table[i].priority,
               process_table[i].burst_time);
    }
}

// Change the state of a process
void change_state(int pid, char *new_state) {
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].pid == pid) {
            char event[100];
            snprintf(event, sizeof(event), "Changed State: PID=%d, Name=%s, From=%s To=%s",
                     pid, process_table[i].name, process_table[i].state, new_state);
            log_event(event);

            printf("%s\n", event);
            strcpy(process_table[i].state, new_state);
            return;
        }
    }
    printf("Error: Process with PID=%d not found.\n", pid);
}

// Round Robin Scheduling
void round_robin_scheduling() {
    printf("\n=== Round Robin Scheduling ===\n");
    int time = 0, completed = 0;

    while (completed < process_count) {
        for (int i = 0; i < process_count; i++) {
            if (process_table[i].burst_time > 0) {
                printf("Time %d: Executing PID=%d (%s)\n", time, process_table[i].pid, process_table[i].name);
                char event[100];
                snprintf(event, sizeof(event), "Round Robin: Executing PID=%d (%s)", process_table[i].pid, process_table[i].name);
                log_event(event);

                if (process_table[i].burst_time <= TIME_QUANTUM) {
                    time += process_table[i].burst_time;
                    process_table[i].burst_time = 0;
                    strcpy(process_table[i].state, "Terminated");
                    completed++;
                    printf("Process PID=%d completed.\n", process_table[i].pid);
                    snprintf(event, sizeof(event), "Process PID=%d completed", process_table[i].pid);
                    log_event(event);
                } else {
                    process_table[i].burst_time -= TIME_QUANTUM;
                    time += TIME_QUANTUM;
                    strcpy(process_table[i].state, "Waiting");
                }
            }
        }
    }
    printf("All processes completed at time %d.\n", time);
}

// Priority Scheduling
void priority_scheduling() {
    printf("\n=== Priority Scheduling ===\n");
    // Sort processes by priority
    for (int i = 0; i < process_count - 1; i++) {
        for (int j = i + 1; j < process_count; j++) {
            if (process_table[i].priority > process_table[j].priority) {
                Process temp = process_table[i];
                process_table[i] = process_table[j];
                process_table[j] = temp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < process_count; i++) {
        if (strcmp(process_table[i].state, "Terminated") != 0) {
            printf("Time %d: Executing PID=%d (%s)\n", time, process_table[i].pid, process_table[i].name);
            time += process_table[i].burst_time;
            process_table[i].burst_time = 0;
            strcpy(process_table[i].state, "Terminated");
            printf("Process PID=%d completed.\n", process_table[i].pid);
        }
    }
    printf("All processes completed at time %d.\n", time);
}

// View logs
void view_logs() {
    char line[200];
    FILE *log_file = fopen(LOG_FILE, "r");
    if (log_file == NULL) {
        printf("Error: Unable to open log file.\n");
        return;
    }

    printf("\n=== Logs ===\n");
    while (fgets(line, sizeof(line), log_file)) {
        printf("%s", line);
    }
    fclose(log_file);
}

void my_process() {
    int choice, pid, priority, burst_time;
    char name[20], state[20];

    while (1) {
        printf("\n=== Mini Operating System ===\n");
        printf("1. Create Process\n");
        printf("2. List Processes\n");
        printf("3. Change Process State\n");
        printf("4. Round Robin Scheduling\n");
        printf("5. Priority Scheduling\n");
        printf("6. View Logs\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process name: ");
                scanf("%s", name);
                printf("Enter priority: ");
                scanf("%d", &priority);
                printf("Enter burst time: ");
                scanf("%d", &burst_time);
                create_process(name, priority, burst_time);
                break;
            case 2:
                list_processes();
                break;
            case 3:
                printf("Enter PID to change state: ");
                scanf("%d", &pid);
                printf("Enter new state (Running/Waiting/Blocked/Terminated): ");
                scanf("%s", state);
                change_state(pid, state);
                break;
            case 4:
                round_robin_scheduling();
                break;
            case 5:
                priority_scheduling();
                break;
            case 6:
                view_logs();
                break;
            case 7:
                printf("Exiting Process Management.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

}

																																																																																																																																																																																																																																																																																																																																																																																																																												
