// scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int end_time;
} Process2;

// Function prototypes
void display_gantt_chart(Process2 processes[], int n);
void fcfs(Process2 processes[], int n);
void sjf(Process2 processes[], int n);
void run_scheduler();

#endif // SCHEDULER_H
