/*
 * graphics.h
 * Header file for the 2D Graphics Editor
 * Declares canvas structure and function prototypes
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

// Canvas dimensions
#define CANVAS_HEIGHT 20
#define CANVAS_WIDTH 50

// Canvas structure
typedef struct {
    char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
} Canvas;

// Function prototypes
void initializeCanvas(Canvas *c);
void displayCanvas(Canvas *c);
void clearCanvas(Canvas *c);

#endif // GRAPHICS_H
