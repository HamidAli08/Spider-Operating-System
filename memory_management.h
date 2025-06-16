#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>

// Constants
#define MAX_PROCESSES 10
#define TOTAL_MEMORY 1024  // Total memory in KB

// Process structure definition
typedef struct {
    int pid;                // Process ID
    int memory_required;    // Memory required by the process
    int allocated;          // Allocation status (1 for allocated, 0 for deallocated)
    int start_address;      // Start address of the allocated memory
} Process1;
// Function prototypes
void create_memory_process(int pid, int memory_required);
void deallocate_memory(int pid);
void display_memory();
void handle_memory_management();

#endif // MEMORY_MANAGEMENT_H
