/*
 * graphics.c
 * Implementation of graphics editor functions
 */

#include <stdio.h>
#include "graphics.h"

/*
 * initializeCanvas
 * Fills the canvas with underscore ('_') characters
 * Parameters: pointer to Canvas structure
 */
void initializeCanvas(Canvas *c) {
    int i, j;
    
    // Iterate through all rows
    for (i = 0; i < CANVAS_HEIGHT; i++) {
        // Iterate through all columns
        for (j = 0; j < CANVAS_WIDTH; j++) {
            c->canvas[i][j] = '_';
        }
    }
}

/*
 * displayCanvas
 * Prints the current canvas to the screen
 * Parameters: pointer to Canvas structure
 */
void displayCanvas(Canvas *c) {
    int i, j;
    
    printf("\n");
    
    // Iterate through all rows
    for (i = 0; i < CANVAS_HEIGHT; i++) {
        // Iterate through all columns
        for (j = 0; j < CANVAS_WIDTH; j++) {
            printf("%c", c->canvas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
