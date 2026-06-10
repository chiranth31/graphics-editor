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
    printf("4. Draw Triangle\n");
    printf("5. Draw Circle\n");
    printf("6. Clear Canvas\n");
    printf("7. List Objects\n");
    printf("8. Delete Object\n");
    printf("9. Modify Object\n");
    printf("10. Exit\n");
    printf("========================================\n");
    printf("Enter your choice (1-10): ");
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
    // Initialize object storage
    initObjectList();
    
    printf("Welcome to the 2D Graphics Editor!\n");
    printf("(Press Enter after each menu choice)\n");
    
    // Continuous menu loop - runs until user selects Exit (option 7)
    while (1) {
        displayMenu();
        
        // Validate input: check if scanf successfully read an integer
        inputStatus = scanf("%d", &choice);
        
        // If scanf failed (user entered non-integer input)
        if (inputStatus != 1) {
            // Clear the invalid input from the buffer
            clearInputBuffer();

            // Notify user of the error
            printf("ERROR: Invalid input! Please enter a numeric choice (1-8).\n");
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
                {
                    int id = addRectangleObject(x, y, width, height);
                    printf("Rectangle drawn at (%d, %d) with width %d and height %d.\n", x, y, width, height);
                    if (id > 0) printf("Object id: %d\n", id);
                }
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
                  {
                      int id = addLineObject(x, y, length, horizontal ? 1 : 0);
                      printf("Line drawn at (%d, %d) with length %d, %s.\n", x, y, length,
                          horizontal ? "horizontal" : "vertical");
                      if (id > 0) printf("Object id: %d\n", id);
                  }
                break;
            }
            case 4: {
                // Draw Triangle option
                int x1, y1, x2, y2, x3, y3;
                printf("Enter x1, y1, x2, y2, x3, y3: ");
                if (scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
                    clearInputBuffer();
                    printf("ERROR: Invalid triangle input! Please enter six integers.\n");
                    break;
                }
                clearInputBuffer();
                drawTriangle(&canvas, x1, y1, x2, y2, x3, y3);
                  {
                      int id = addTriangleObject(x1, y1, x2, y2, x3, y3);
                      printf("Triangle drawn with vertices (%d, %d), (%d, %d), (%d, %d).\n",
                          x1, y1, x2, y2, x3, y3);
                      if (id > 0) printf("Object id: %d\n", id);
                  }
                break;
            }
            case 5: {
                // Draw Circle option
                int cx, cy, radius;
                printf("Enter center x, center y, radius: ");
                if (scanf("%d %d %d", &cx, &cy, &radius) != 3) {
                    clearInputBuffer();
                    printf("ERROR: Invalid circle input! Please enter three integers.\n");
                    break;
                }
                clearInputBuffer();
                if (radius <= 0) {
                    printf("ERROR: Radius must be a positive value.\n");
                    break;
                }
                drawCircle(&canvas, cx, cy, radius);
                {
                    int id = addCircleObject(cx, cy, radius);
                    printf("Circle drawn at center (%d, %d) with radius %d.\n", cx, cy, radius);
                    if (id > 0) printf("Object id: %d\n", id);
                }
                break;
            }
            case 6:
                // Clear Canvas option - resets all pixels to underscore
                clearCanvas(&canvas);
                printf("Canvas has been cleared!\n");
                break;

            case 7:
                // List stored objects
                listObjects();
                break;

            case 8: {
                int id;
                printf("Enter object id to delete: ");
                if (scanf("%d", &id) != 1) {
                    clearInputBuffer();
                    printf("ERROR: Invalid input! Please enter a numeric object id.\n");
                    break;
                }
                clearInputBuffer();
                if (deleteObject(id)) {
                    redrawObjects(&canvas);
                    printf("Object %d deleted. Canvas redrawn.\n", id);
                    listObjects();
                } else {
                    printf("Object id %d not found. No changes made.\n", id);
                }
                break;
            }

            case 9: {
                int id;
                printf("Enter object id to modify: ");
                if (scanf("%d", &id) != 1) {
                    clearInputBuffer();
                    printf("ERROR: Invalid input! Please enter a numeric object id.\n");
                    break;
                }
                clearInputBuffer();

                GraphicalObject *obj = getObjectById(id);
                if (obj == NULL) {
                    printf("Object id %d not found. No changes made.\n", id);
                    break;
                }

                GraphicalObject updated = *obj;
                updated.type = obj->type;

                switch (obj->type) {
                    case OBJ_RECTANGLE: {
                        int x, y, width, height;
                        printf("Current rectangle: (%d, %d) w=%d h=%d\n",
                               obj->data.rect.x, obj->data.rect.y,
                               obj->data.rect.width, obj->data.rect.height);
                        printf("Enter new x, y, width, height: ");
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
                        updated.data.rect.x = x;
                        updated.data.rect.y = y;
                        updated.data.rect.width = width;
                        updated.data.rect.height = height;
                        break;
                    }
                    case OBJ_LINE: {
                        int x, y, length, horizontal;
                        printf("Current line: (%d, %d) len=%d %s\n",
                               obj->data.line.x, obj->data.line.y,
                               obj->data.line.length,
                               obj->data.line.horizontal ? "horizontal" : "vertical");
                        printf("Enter new x, y, length, horizontal(1=horizontal,0=vertical): ");
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
                        updated.data.line.x = x;
                        updated.data.line.y = y;
                        updated.data.line.length = length;
                        updated.data.line.horizontal = horizontal ? 1 : 0;
                        break;
                    }
                    case OBJ_TRIANGLE: {
                        int x1, y1, x2, y2, x3, y3;
                        printf("Current triangle: (%d, %d)-(%d, %d)-(%d, %d)\n",
                               obj->data.tri.x1, obj->data.tri.y1,
                               obj->data.tri.x2, obj->data.tri.y2,
                               obj->data.tri.x3, obj->data.tri.y3);
                        printf("Enter new x1, y1, x2, y2, x3, y3: ");
                        if (scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
                            clearInputBuffer();
                            printf("ERROR: Invalid triangle input! Please enter six integers.\n");
                            break;
                        }
                        clearInputBuffer();
                        updated.data.tri.x1 = x1;
                        updated.data.tri.y1 = y1;
                        updated.data.tri.x2 = x2;
                        updated.data.tri.y2 = y2;
                        updated.data.tri.x3 = x3;
                        updated.data.tri.y3 = y3;
                        break;
                    }
                    case OBJ_CIRCLE: {
                        int cx, cy, radius;
                        printf("Current circle: center=(%d, %d) r=%d\n",
                               obj->data.circ.cx, obj->data.circ.cy,
                               obj->data.circ.radius);
                        printf("Enter new center x, center y, radius: ");
                        if (scanf("%d %d %d", &cx, &cy, &radius) != 3) {
                            clearInputBuffer();
                            printf("ERROR: Invalid circle input! Please enter three integers.\n");
                            break;
                        }
                        clearInputBuffer();
                        if (radius <= 0) {
                            printf("ERROR: Radius must be a positive value.\n");
                            break;
                        }
                        updated.data.circ.cx = cx;
                        updated.data.circ.cy = cy;
                        updated.data.circ.radius = radius;
                        break;
                    }
                    default:
                        printf("ERROR: Unknown object type. Cannot modify.\n");
                        break;
                }

                if (modifyObject(id, &updated)) {
                    redrawObjects(&canvas);
                    printf("Object %d modified. Canvas redrawn.\n", id);
                    listObjects();
                } else {
                    printf("Failed to modify object %d.\n", id);
                }
                break;
            }

            case 10:
                // Exit option - terminates the program
                printf("Thank you for using the 2D Graphics Editor!\n");
                exit(0);
                break;

            default:
                // Invalid choice - user entered a number outside valid range (1-8)
                printf("Invalid choice! Please enter 1, 2, 3, 4, 5, 6, 7, or 8.\n");
                break;
        }
    }
    
    return 0;
}
