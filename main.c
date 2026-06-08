/*
 * main.c
 * Main menu driver for the 2D Graphics Editor
 * Handles user input validation and menu-driven operations
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

/*
 * displayMenu
 * Displays the main menu options to the user
 * Output: Prints formatted menu with all available options
 */
void displayMenu(void) {
    printf("\n");
    printf("========== 2D Graphics Editor ==========\n");
    printf("1. Display Picture\n");
    printf("2. Clear Canvas\n");
    printf("3. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-3): ");
}

/*
 * clearInputBuffer
 * Clears the input buffer of any leftover characters
 * This prevents invalid input from causing infinite loops
 */
void clearInputBuffer(void) {
    int c;
    // Read and discard characters until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * main
 * Main function - initializes canvas and handles menu-driven operations
 * Features: Input validation, error handling, and continuous menu loop
 * Returns: 0 on successful exit
 */
int main(void) {
    Canvas canvas;
    int choice;
    int inputStatus;
    
    // Initialize the canvas with '_' characters
    initializeCanvas(&canvas);
    
    printf("Welcome to the 2D Graphics Editor!\n");
    printf("(Press Enter after each menu choice)\n");
    
    // Continuous menu loop - runs until user selects Exit (option 3)
    while (1) {
        displayMenu();
        
        // Validate input: check if scanf successfully read an integer
        inputStatus = scanf("%d", &choice);
        
        // If scanf failed (user entered non-integer input)
        if (inputStatus != 1) {
            // Clear the invalid input from the buffer
            clearInputBuffer();
            
            // Notify user of the error
            printf("ERROR: Invalid input! Please enter a numeric choice (1-3).\n");
            continue;  // Skip to next iteration of menu loop
        }
        
        // Handle user's choice with input validation
        switch (choice) {
            case 1:
                // Display Picture option
                printf("\nCurrent Canvas:\n");
                displayCanvas(&canvas);
                break;
                
            case 2:
                // Clear Canvas option - resets all pixels to underscore
                clearCanvas(&canvas);
                printf("Canvas has been cleared!\n");
                break;
                
            case 3:
                // Exit option - terminates the program
                printf("Thank you for using the 2D Graphics Editor!\n");
                exit(0);
                break;
                
            default:
                // Invalid choice - user entered a number outside valid range (1-3)
                printf("Invalid choice! Please enter 1, 2, or 3.\n");
                break;
        }
    }
    
    return 0;
}
