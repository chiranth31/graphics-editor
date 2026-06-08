/*
 * main.c
 * Main menu driver for the 2D Graphics Editor
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

/*
 * displayMenu
 * Displays the main menu options to the user
 */
void displayMenu(void) {
    printf("\n");
    printf("========== 2D Graphics Editor ==========\n");
    printf("1. Display Picture\n");
    printf("2. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

/*
 * main
 * Main function - initializes canvas and handles menu-driven operations
 */
int main(void) {
    Canvas canvas;
    int choice;
    
    // Initialize the canvas with '_' characters
    initializeCanvas(&canvas);
    
    printf("Welcome to the 2D Graphics Editor!\n");
    
    // Menu loop
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        // Handle user choice
        switch (choice) {
            case 1:
                // Display Picture option
                printf("\nCurrent Canvas:\n");
                displayCanvas(&canvas);
                break;
                
            case 2:
                // Exit option
                printf("Thank you for using the 2D Graphics Editor!\n");
                exit(0);
                break;
                
            default:
                // Invalid choice
                printf("Invalid choice! Please enter 1 or 2.\n");
                break;
        }
    }
    
    return 0;
}
