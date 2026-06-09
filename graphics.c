/*
 * graphics.c
 * Implementation of graphics editor functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

/*
 * drawLine
 * Draws a horizontal or vertical line using '*' characters.
 * If horizontal is non-zero, draws from (x, y) to the right.
 * If horizontal is zero, draws from (x, y) downward.
 */
void drawLine(Canvas *c, int x, int y, int length, int horizontal) {
    int i;
    
    if (horizontal) {
        for (i = x; i < x + length; i++) {
            if (y >= 0 && y < CANVAS_HEIGHT && i >= 0 && i < CANVAS_WIDTH) {
                c->canvas[y][i] = '*';
            }
        }
    } else {
        for (i = y; i < y + length; i++) {
            if (x >= 0 && x < CANVAS_WIDTH && i >= 0 && i < CANVAS_HEIGHT) {
                c->canvas[i][x] = '*';
            }
        }
    }
}

/*
 * drawCircle
 * Draws an approximate circle using '*' characters at the specified center and radius.
 */
void drawCircle(Canvas *c, int centerX, int centerY, int radius) {
    int dx, dy;
    int x, y;

    if (radius <= 0) {
        return;
    }

    for (dx = -radius; dx <= radius; dx++) {
        y = (int)(centerY + 0.5 + sqrt((double)(radius * radius - dx * dx)));
        x = centerX + dx;
        if (y >= 0 && y < CANVAS_HEIGHT && x >= 0 && x < CANVAS_WIDTH) {
            c->canvas[y][x] = '*';
        }

        y = (int)(centerY - 0.5 - sqrt((double)(radius * radius - dx * dx)));
        if (y >= 0 && y < CANVAS_HEIGHT && x >= 0 && x < CANVAS_WIDTH) {
            c->canvas[y][x] = '*';
        }
    }

    for (dy = -radius; dy <= radius; dy++) {
        x = (int)(centerX + 0.5 + sqrt((double)(radius * radius - dy * dy)));
        y = centerY + dy;
        if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
            c->canvas[y][x] = '*';
        }

        x = (int)(centerX - 0.5 - sqrt((double)(radius * radius - dy * dy)));
        if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
            c->canvas[y][x] = '*';
        }
    }
}

/*
 * drawGeneralLine
 * Draws a straight line between any two canvas points using Bresenham's algorithm.
 * This helper is used to render triangle edges cleanly.
 */
static void drawGeneralLine(Canvas *c, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1) {
        if (x1 >= 0 && x1 < CANVAS_WIDTH && y1 >= 0 && y1 < CANVAS_HEIGHT) {
            c->canvas[y1][x1] = '*';
        }
        if (x1 == x2 && y1 == y2) {
            break;
        }
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

/*
 * drawTriangle
 * Draws a triangle by connecting three coordinates with '*' characters.
 * Parameters: pointer to Canvas structure and three vertex coordinate pairs.
 */
void drawTriangle(Canvas *c, int x1, int y1, int x2, int y2, int x3, int y3) {
    drawGeneralLine(c, x1, y1, x2, y2);
    drawGeneralLine(c, x2, y2, x3, y3);
    drawGeneralLine(c, x3, y3, x1, y1);
}
