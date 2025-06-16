#ifndef MINI_OS_H
#define MINI_OS_H

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2
#define LOG_FILE "process_logs.txt"

// Define the Process structure
typedef struct {
    int pid;
    char name[20];
    char state[20]; // Running, Waiting, Blocked, Terminated
    int priority;
    int burst_time;
} Process;

// Declare the process table and other global variables
extern Process process_table[MAX_PROCESSES];
extern int process_count;

// Function declarations
void log_event(const char *event);
void create_process(char *name, int priority, int burst_time);
void list_processes();
void change_state(int pid, char *new_state);
void round_robin_scheduling();
void priority_scheduling();
void view_logs();
void my_process();

#endif // MINI_OS_H

