#include <stdio.h>
#include <stdlib.h>
#include "memory_management.h"  // Include the header file

// Define the process table and global variables
Process1 process_table_memory[MAX_PROCESSES];
int process_count = 0;
int memory_allocated = 0;

// Function to create a process and allocate memory
void create_memory_process(int pid, int memory_required) {
    if (process_count >= MAX_PROCESSES) {
        printf("Error: Maximum process limit reached.\n");
        return;
    }

    if (memory_required > (TOTAL_MEMORY - memory_allocated)) {
        printf("Error: Not enough memory available to allocate for PID=%d.\n", pid);
        return;
    }

    process_table_memory[process_count].pid = pid;
    process_table_memory[process_count].memory_required = memory_required;
    process_table_memory[process_count].allocated = 1;
    process_table_memory[process_count].start_address = memory_allocated;

    memory_allocated += memory_required;
    process_count++;

    printf("Process created: PID=%d, Memory Allocated=%d KB, Start Address=%d KB\n",
           pid, memory_required, process_table_memory[process_count - 1].start_address);
}

// Function to deallocate memory of a process
void deallocate_memory(int pid) {
    for (int i = 0; i < process_count; i++) {
        if (process_table_memory[i].pid == pid && process_table_memory[i].allocated == 1) {
            printf("Deallocating memory for PID=%d: %d KB freed.\n",
                   pid, process_table_memory[i].memory_required);

            memory_allocated -= process_table_memory[i].memory_required;
            process_table_memory[i].allocated = 0;
            process_table_memory[i].memory_required = 0;
            return;
        }
    }
    printf("Error: Process with PID=%d not found or memory already deallocated.\n", pid);
}

// Function to display memory allocation
void display_memory() {
    printf("\n=== Memory Allocation ===\n");
    printf("PID\tStart Address (KB)\tMemory Allocated (KB)\n");
    for (int i = 0; i < process_count; i++) {
        if (process_table_memory[i].allocated) {
            printf("%d\t%d\t\t\t%d\n",
                   process_table_memory[i].pid, process_table_memory[i].start_address, process_table_memory[i].memory_required);
        }
    }
    printf("Total Memory: %d KB, Used: %d KB, Free: %d KB\n",
           TOTAL_MEMORY, memory_allocated, TOTAL_MEMORY - memory_allocated);
}

// Function to handle user choices
void handle_memory_management() {
    int choice, pid, memory_required;

    while (1) {
        printf("\n=== Memory Management System ===\n");
        printf("1. Create Process\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory Allocation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter PID: ");
                scanf("%d", &pid);
                printf("Enter memory required (in KB): ");
                scanf("%d", &memory_required);
                create_memory_process(pid, memory_required);
                break;
            case 2:
                printf("Enter PID to deallocate memory: ");
                scanf("%d", &pid);
                deallocate_memory(pid);
                break;
            case 3:
                display_memory();
                break;
            case 4:
                printf("Exiting Memory Management System.\n");
                return;  // Return to main menu instead of exiting the entire program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

