#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"


// Function to play Rock, Paper, Scissors
void play_rock_paper_scissors() {
    int user_choice, computer_choice;
    while (1) {
        printf("\n\n--- New Round ---\n");
        user_choice = get_user_choice();
        computer_choice = get_computer_choice();
        
        determine_winner(user_choice, computer_choice);
        
        char play_again;
        printf("\nDo you want to play again? (y/n): ");
        getchar();  // Clear the input buffer
        scanf("%c", &play_again);
        
        if (play_again != 'y' && play_again != 'Y') {
            break;  // Exit the inner loop to go back to the main menu
        }
    }
}



// Function to display the menu and take user input for Rock, Paper, Scissors
int get_user_choice() {
    int choice;
    printf("\nRock, Paper, Scissors Game!\n");
    printf("1. Rock\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");
    printf("Enter your choice (1, 2, or 3): ");
    scanf("%d", &choice);
    
    while (choice < 1 || choice > 3) {
        printf("Invalid choice! Please select 1 for Rock, 2 for Paper, or 3 for Scissors: ");
        scanf("%d", &choice);
    }
    
    return choice;
}

// Function to get the computer's random choice
int get_computer_choice() {
    return rand() % 3 + 1;  // Random number between 1 and 3
}

// Function to determine the winner of the game
void determine_winner(int user_choice, int computer_choice) {
    printf("\nYou chose: ");
    switch (user_choice) {
        case 1: printf("Rock\n"); break;
        case 2: printf("Paper\n"); break;
        case 3: printf("Scissors\n"); break;
    }

    printf("Computer chose: ");
    switch (computer_choice) {
        case 1: printf("Rock\n"); break;
        case 2: printf("Paper\n"); break;
        case 3: printf("Scissors\n"); break;
    }

    if (user_choice == computer_choice) {
        printf("It's a draw!\n");
    } else if ((user_choice == 1 && computer_choice == 3) || 
               (user_choice == 2 && computer_choice == 1) || 
               (user_choice == 3 && computer_choice == 2)) {
        printf("You win!\n");
    } else {
        printf("You lose!\n");
    }
}

