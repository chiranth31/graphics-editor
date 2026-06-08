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
 * Prints the current canvas with borders and row/column formatting
 * Parameters: pointer to Canvas structure
 */
void displayCanvas(Canvas *c) {
    int i, j;
    
    printf("\n");
    printf("+");
    for (j = 0; j < CANVAS_WIDTH; j++) {
        printf("-");
    }
    printf("+\n");
    
    // Iterate through all rows
    for (i = 0; i < CANVAS_HEIGHT; i++) {
        printf("|");
        // Iterate through all columns
        for (j = 0; j < CANVAS_WIDTH; j++) {
            printf("%c", c->canvas[i][j]);
        }
        printf("|\n");
    }
    
    printf("+");
    for (j = 0; j < CANVAS_WIDTH; j++) {
        printf("-");
    }
    printf("+\n\n");
}

/*
 * clearCanvas
 * Resets the canvas to all underscore ('_') characters
 * Parameters: pointer to Canvas structure
 */
void clearCanvas(Canvas *c) {
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
 * drawRectangle
 * Draws a rectangle using '*' characters on the canvas.
 * (x, y) is the top-left corner of the rectangle.
 * Parameters: pointer to Canvas structure, x-coordinate, y-coordinate,
 * width and height of the rectangle.
 */
void drawRectangle(Canvas *c, int x, int y, int width, int height) {
    int i, j;
    int xEnd = x + width - 1;
    int yEnd = y + height - 1;
    
    // Draw horizontal edges if dimensions are valid
    for (j = x; j <= xEnd; j++) {
        if (y >= 0 && y < CANVAS_HEIGHT && j >= 0 && j < CANVAS_WIDTH) {
            c->canvas[y][j] = '*';
        }
        if (yEnd >= 0 && yEnd < CANVAS_HEIGHT && j >= 0 && j < CANVAS_WIDTH) {
            c->canvas[yEnd][j] = '*';
        }
    }
    
    // Draw vertical edges
    for (i = y; i <= yEnd; i++) {
        if (x >= 0 && x < CANVAS_WIDTH && i >= 0 && i < CANVAS_HEIGHT) {
            c->canvas[i][x] = '*';
        }
        if (xEnd >= 0 && xEnd < CANVAS_WIDTH && i >= 0 && i < CANVAS_HEIGHT) {
            c->canvas[i][xEnd] = '*';
        }
    }
}
