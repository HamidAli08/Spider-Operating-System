#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int end_time;
} Process2;

// Function to visualize the Gantt chart
void display_gantt_chart(Process2 processes[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].pid);
        for (int j = 0; j < processes[i].burst_time; j++) {
            printf("=");
        }
        printf(" ");
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burst_time; j++) {
            printf(" ");
        }
        printf("%2d", processes[i].end_time);
    }
    printf("\n");
}

// Function to simulate FCFS scheduling
void fcfs(Process2 processes[], int n) {
    printf("\nFirst Come First Serve (FCFS) Scheduling:\n");
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].start_time = current_time;
        processes[i].end_time = current_time + processes[i].burst_time;
        current_time = processes[i].end_time;
    }

    // Display process information
    printf("PID\tArrival\tBurst\tStart\tEnd\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].start_time, processes[i].end_time);
    }

    // Display Gantt chart
    display_gantt_chart(processes, n);
}

// Function to simulate SJF scheduling
void sjf(Process2 processes[], int n) {
    printf("\nShortest Job First (SJF) Scheduling:\n");

    // Sort processes by arrival time, then burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time &&
                 processes[j].burst_time > processes[j + 1].burst_time)) {
                Process2 temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completed = 0, current_time = 0;
    int visited[MAX_PROCESSES] = {0};

    while (completed < n) {
        int idx = -1, min_burst = 99999;

        // Find process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        processes[idx].start_time = current_time;
        processes[idx].end_time = current_time + processes[idx].burst_time;
        current_time = processes[idx].end_time;
        visited[idx] = 1;
        completed++;
    }

    // Display process information
    printf("PID\tArrival\tBurst\tStart\tEnd\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].start_time, processes[i].end_time);
    }

    // Display Gantt chart
    display_gantt_chart(processes, n);
}

// Main function to execute scheduling
void run_scheduler() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process2 processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            sjf(processes, n);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

