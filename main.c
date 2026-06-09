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
    printf("2. Draw Rectangle\n");
    printf("3. Draw Line\n");
    printf("4. Clear Canvas\n");
    printf("5. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-5): ");
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
    
    // Continuous menu loop - runs until user selects Exit (option 5)
    while (1) {
        displayMenu();
        
        // Validate input: check if scanf successfully read an integer
        inputStatus = scanf("%d", &choice);
        
        // If scanf failed (user entered non-integer input)
        if (inputStatus != 1) {
            // Clear the invalid input from the buffer
            clearInputBuffer();
            
            // Notify user of the error
            printf("ERROR: Invalid input! Please enter a numeric choice (1-5).\n");
            continue;  // Skip to next iteration of menu loop
        }
        
        // Handle user's choice with input validation
        switch (choice) {
            case 1:
                // Display Picture option
                printf("\nCurrent Canvas:\n");
                displayCanvas(&canvas);
                break;
                
            case 2: {
                // Draw Rectangle option
                int x, y, width, height;
                printf("Enter x, y, width, height: ");
                if (scanf("%d %d %d %d", &x, &y, &width, &height) != 4) {
                    clearInputBuffer();
                    printf("ERROR: Invalid rectangle input! Please enter four integers.\n");
                    break;
                }
                clearInputBuffer();
                if (width <= 0 || height <= 0) {
                    printf("ERROR: Width and height must be positive values.\n");
                    break;
                }
                drawRectangle(&canvas, x, y, width, height);
                printf("Rectangle drawn at (%d, %d) with width %d and height %d.\n", x, y, width, height);
                break;
            }
            case 3: {
                // Draw Line option
                int x, y, length, horizontal;
                printf("Enter x, y, length, horizontal(1=horizontal,0=vertical): ");
                if (scanf("%d %d %d %d", &x, &y, &length, &horizontal) != 4) {
                    clearInputBuffer();
                    printf("ERROR: Invalid line input! Please enter four integers.\n");
                    break;
                }
                clearInputBuffer();
                if (length <= 0) {
                    printf("ERROR: Length must be a positive value.\n");
                    break;
                }
                drawLine(&canvas, x, y, length, horizontal ? 1 : 0);
                printf("Line drawn at (%d, %d) with length %d, %s.\n", x, y, length,
                       horizontal ? "horizontal" : "vertical");
                break;
            }
            case 4:
                // Clear Canvas option - resets all pixels to underscore
                clearCanvas(&canvas);
                printf("Canvas has been cleared!\n");
                break;
                
            case 5:
                // Exit option - terminates the program
                printf("Thank you for using the 2D Graphics Editor!\n");
                exit(0);
                break;
                
            default:
                // Invalid choice - user entered a number outside valid range (1-5)
                printf("Invalid choice! Please enter 1, 2, 3, 4, or 5.\n");
                break;
        }
    }
    
    return 0;
}
