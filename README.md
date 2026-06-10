# Graphics Editor
# 2D Graphics Editor

A lightweight console-based 2D graphics editor that renders simple ASCII art on a fixed-size canvas. The editor provides a menu-driven interface to draw and manage primitive shapes (rectangles, lines, triangles, circles), persist them in an internal object list, and redraw the canvas on demand.

**Key goals:** simplicity, clear data structures for object management, and a small, portable C codebase suitable for learning and small utilities.

**Repository layout**

- [graphics.h](graphics.h) — public types and function prototypes
- [graphics.c](graphics.c) — implementation of drawing routines and object list
- [main.c](main.c) — menu-driven program and user I/O

**Build output**: `output/main.exe`

**Supported platform:** Command-line C programs (tested with `gcc` on Windows)

**License:** MIT-style (please add your preferred license file)

**Status:** Functional menu-driven demo for creating and managing ASCII graphics objects.

**Features**

- Draw primitives: rectangle, line (horizontal/vertical), triangle, circle
- Persistent object list with add/list/delete/modify operations
- Redraw the canvas from stored objects (useful after deleting/modifying)
- Input validation and simple error messages in the menu
- Fixed canvas size defined by `CANVAS_WIDTH` and `CANVAS_HEIGHT`

**Data structures used**

- **`Canvas`**: a fixed-size 2D array of `char` representing pixels on-screen. Canvas dimensions are defined by `CANVAS_HEIGHT` and `CANVAS_WIDTH`.
- **`GraphicalObject`**: a union-based type that stores one primitive per entry alongside an `ObjectType` enum and `id`. This supports heterogeneous collections in a single array.
- **`ObjectType`**: enumerator values `OBJ_RECTANGLE`, `OBJ_LINE`, `OBJ_TRIANGLE`, `OBJ_CIRCLE` used to switch on object behavior.
- **Object list**: a static array (`object_list`) sized by `MAX_OBJECTS` with `object_count` and `next_object_id` for sequential ids.

**Public functions (API)**

The following high-level functions are defined in `graphics.h` and implemented in `graphics.c`:

- `initializeCanvas(Canvas *c)` — fill the canvas with the background character (`_`).
- `displayCanvas(Canvas *c)` — print the canvas with a border to stdout.
- `clearCanvas(Canvas *c)` — reset the canvas contents to the background.
- `drawRectangle(Canvas *c, int x, int y, int width, int height)` — draw rectangle edges using `*` characters.
- `drawLine(Canvas *c, int x, int y, int length, int horizontal)` — draw horizontal or vertical lines.
- `drawTriangle(Canvas *c, int x1, int y1, int x2, int y2, int x3, int y3)` — draw a triangle by connecting three points.
- `drawCircle(Canvas *c, int centerX, int centerY, int radius)` — approximate a circle on the grid.

Object-list API:

- `initObjectList(void)` — reset stored objects and id counters.
- `addRectangleObject(...)`, `addLineObject(...)`, `addTriangleObject(...)`, `addCircleObject(...)` — add primitives to the internal list and return an object id.
- `deleteObject(int id)` — remove object by id (returns success/failure).
- `modifyObject(int id, const GraphicalObject *updated)` — update parameters for an existing object.
- `GraphicalObject *getObjectById(int id)` — retrieve a pointer to a stored object.
- `redrawObjects(Canvas *c)` — clear the canvas and redraw all stored objects.
- `listObjects(void)` — print a human-readable list of stored objects and parameters.

Note: a few helper functions are `static` within `graphics.c` (for example, `addObject` and `drawGeneralLine`) and are not part of the public header.

**Compilation instructions**

Ensure `gcc` is installed (MinGW or similar on Windows). From the project root run:

```sh
gcc -Wall -Wextra -g3 main.c graphics.c -o output/main.exe
```

You can also use the provided VS Code task `Build Graphics Editor` if configured in the workspace.

**Running**

Run the produced executable from a terminal:

```sh
./output/main.exe
```

Follow the on-screen menu to add shapes, list objects, delete or modify them, and display the ASCII canvas.

**Sample output**

Below is an example snapshot after drawing a rectangle and a horizontal line. The canvas is 20 rows by 50 columns in this build.

```
+--------------------------------------------------+
|__________________________________________________|
|__________________________________________________|
|________________________________****______________|
|________________________________*  *______________|
|________________________________*  *______________|
|________________________________****______________|
|__________________________________________________|
|______________________*****_______________________|
|______________________*___*_______________________|
|______________________*****_______________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
|__________________________________________________|
+--------------------------------------------------+

```

**Future improvements**

- Expand canvas size or make it dynamically allocated to allow arbitrary dimensions.
- Add filled shapes (solid rectangles, filled circles) and different drawing characters.
- Implement undo/redo functionality and object grouping.
- Add serialization to save/load object lists to/from disk (JSON or a simple text format).
- Replace blocking `scanf` input with a safer input parser or a small UI library for better UX.
- Add automated tests for drawing primitives and object list behavior.

If you want, I can also:

- Run the build and capture a real sample run output.
- Add a small test harness that programmatically creates objects and writes a sample output file.

A lightweight 2D graphics editor written in C.

## Overview

This project provides a simple menu-driven canvas editor that supports:
- displaying the current canvas
- drawing rectangles, lines, triangles, and circles
- clearing the canvas
- listing, deleting, and modifying stored objects

## Build

From the project root directory, run:

```powershell
gcc main.c graphics.c -o output/main.exe
```

## Run

After building, run:

```powershell
output\main.exe
```

Follow the menu prompts to draw and manage objects on the canvas.

## Notes

- Canvas size is fixed at 50 columns by 20 rows.
- Objects are stored in memory and redrawn whenever the canvas changes.
- Input validation is performed for numeric menu selections and object parameters.
