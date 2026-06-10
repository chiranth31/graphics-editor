# Graphics Editor

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
