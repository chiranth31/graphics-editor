/*
 * graphics.c
 * Implementation of graphics editor functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

// Internal object list storage
static GraphicalObject object_list[MAX_OBJECTS];
static int object_count = 0;
static int next_object_id = 1;

void initObjectList(void) {
    object_count = 0;
    next_object_id = 1;
}

static int addObject(GraphicalObject *obj) {
    if (object_count >= MAX_OBJECTS) return -1;
    obj->id = next_object_id++;
    object_list[object_count++] = *obj;
    return obj->id;
}

int addRectangleObject(int x, int y, int width, int height) {
    GraphicalObject obj;
    obj.type = OBJ_RECTANGLE;
    obj.data.rect.x = x;
    obj.data.rect.y = y;
    obj.data.rect.width = width;
    obj.data.rect.height = height;
    return addObject(&obj);
}

int addLineObject(int x, int y, int length, int horizontal) {
    GraphicalObject obj;
    obj.type = OBJ_LINE;
    obj.data.line.x = x;
    obj.data.line.y = y;
    obj.data.line.length = length;
    obj.data.line.horizontal = horizontal ? 1 : 0;
    return addObject(&obj);
}

int addTriangleObject(int x1, int y1, int x2, int y2, int x3, int y3) {
    GraphicalObject obj;
    obj.type = OBJ_TRIANGLE;
    obj.data.tri.x1 = x1;
    obj.data.tri.y1 = y1;
    obj.data.tri.x2 = x2;
    obj.data.tri.y2 = y2;
    obj.data.tri.x3 = x3;
    obj.data.tri.y3 = y3;
    return addObject(&obj);
}

int addCircleObject(int cx, int cy, int radius) {
    GraphicalObject obj;
    obj.type = OBJ_CIRCLE;
    obj.data.circ.cx = cx;
    obj.data.circ.cy = cy;
    obj.data.circ.radius = radius;
    return addObject(&obj);
}

void listObjects(void) {
    int i;
    if (object_count == 0) {
        printf("No objects stored.\n");
        return;
    }
    printf("\nStored Objects (count=%d):\n", object_count);
    for (i = 0; i < object_count; i++) {
        GraphicalObject *o = &object_list[i];
        switch (o->type) {
            case OBJ_RECTANGLE:
                printf("%d: Rectangle at (%d,%d) w=%d h=%d\n", o->id,
                       o->data.rect.x, o->data.rect.y,
                       o->data.rect.width, o->data.rect.height);
                break;
            case OBJ_LINE:
                printf("%d: Line at (%d,%d) len=%d %s\n", o->id,
                       o->data.line.x, o->data.line.y,
                       o->data.line.length,
                       o->data.line.horizontal ? "horizontal" : "vertical");
                break;
            case OBJ_TRIANGLE:
                printf("%d: Triangle (%d,%d)-(%d,%d)-(%d,%d)\n", o->id,
                       o->data.tri.x1, o->data.tri.y1,
                       o->data.tri.x2, o->data.tri.y2,
                       o->data.tri.x3, o->data.tri.y3);
                break;
            case OBJ_CIRCLE:
                printf("%d: Circle center=(%d,%d) r=%d\n", o->id,
                       o->data.circ.cx, o->data.circ.cy,
                       o->data.circ.radius);
                break;
            default:
                printf("%d: Unknown object type\n", o->id);
        }
    }
    printf("\n");
}

int deleteObject(int id) {
    int i, j;
    int found = -1;

    for (i = 0; i < object_count; i++) {
        if (object_list[i].id == id) {
            found = i;
            break;
        }
    }

    if (found < 0) {
        return 0;
    }

    for (j = found; j < object_count - 1; j++) {
        object_list[j] = object_list[j + 1];
    }
    object_count--;
    return 1;
}

GraphicalObject *getObjectById(int id) {
    int i;
    for (i = 0; i < object_count; i++) {
        if (object_list[i].id == id) {
            return &object_list[i];
        }
    }
    return NULL;
}

int modifyObject(int id, const GraphicalObject *updated) {
    GraphicalObject *obj = getObjectById(id);
    if (obj == NULL || updated == NULL) {
        return 0;
    }

    switch (obj->type) {
        case OBJ_RECTANGLE:
            obj->data.rect = updated->data.rect;
            break;
        case OBJ_LINE:
            obj->data.line = updated->data.line;
            break;
        case OBJ_TRIANGLE:
            obj->data.tri = updated->data.tri;
            break;
        case OBJ_CIRCLE:
            obj->data.circ = updated->data.circ;
            break;
        default:
            return 0;
    }
    return 1;
}

void redrawObjects(Canvas *c) {
    int i;
    clearCanvas(c);

    for (i = 0; i < object_count; i++) {
        GraphicalObject *o = &object_list[i];
        switch (o->type) {
            case OBJ_RECTANGLE:
                drawRectangle(c, o->data.rect.x, o->data.rect.y,
                              o->data.rect.width, o->data.rect.height);
                break;
            case OBJ_LINE:
                drawLine(c, o->data.line.x, o->data.line.y,
                         o->data.line.length, o->data.line.horizontal);
                break;
            case OBJ_TRIANGLE:
                drawTriangle(c, o->data.tri.x1, o->data.tri.y1,
                             o->data.tri.x2, o->data.tri.y2,
                             o->data.tri.x3, o->data.tri.y3);
                break;
            case OBJ_CIRCLE:
                drawCircle(c, o->data.circ.cx, o->data.circ.cy,
                           o->data.circ.radius);
                break;
            default:
                break;
        }
    }
}


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
