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
void drawRectangle(Canvas *c, int x, int y, int width, int height);
void drawLine(Canvas *c, int x, int y, int length, int horizontal);
void drawCircle(Canvas *c, int centerX, int centerY, int radius);
void drawTriangle(Canvas *c, int x1, int y1, int x2, int y2, int x3, int y3);

// Object management
#define MAX_OBJECTS 100

typedef enum {
    OBJ_RECTANGLE,
    OBJ_LINE,
    OBJ_TRIANGLE,
    OBJ_CIRCLE
} ObjectType;

typedef struct {
    ObjectType type;
    int id; // sequential id starting at 1
    union {
        struct { int x, y, width, height; } rect;
        struct { int x, y, length, horizontal; } line;
        struct { int x1, y1, x2, y2, x3, y3; } tri;
        struct { int cx, cy, radius; } circ;
    } data;
} GraphicalObject;

// Object list API
void initObjectList(void);
int addRectangleObject(int x, int y, int width, int height);
int addLineObject(int x, int y, int length, int horizontal);
int addTriangleObject(int x1, int y1, int x2, int y2, int x3, int y3);
int addCircleObject(int cx, int cy, int radius);
void listObjects(void);

#endif // GRAPHICS_H
