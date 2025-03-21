# 3D Transformation Demo

This program demonstrates the fundamental transformations in computer graphics using OpenGL and GLUT. It visualizes a 3D cube with different colored edges on a Cartesian coordinate system and allows interactive manipulation of various transformations.

## Features

### Transformations Demonstrated
1. **Translation** - Moving the cube in 3D space
2. **Rotation** - Rotating the cube around X, Y, and Z axes
3. **Reflection** - Reflecting the cube across X, Y, and Z planes
4. **Shearing** - Applying shear transformations to distort the cube
5. **Scaling** - Resizing the cube uniformly or non-uniformly

### Visual Elements
- A 3D cube with 12 distinctly colored edges
- Visible Cartesian coordinate system (X, Y, Z axes with different colors)
- Grid on the XZ plane for better spatial reference
- On-screen display of current transformation mode and parameters

## Controls

| Key | Function |
|-----|----------|
| M | Switch between transformation modes |
| R | Reset all transformations |
| Arrow keys | Adjust X and Y parameters of current transformation |
| Page Up/Down | Adjust Z parameter of current transformation |
| X | Toggle reflection along X-axis (in Reflection mode) |
| Y | Toggle reflection along Y-axis (in Reflection mode) |
| Z | Toggle reflection along Z-axis (in Reflection mode) |
| ESC | Exit the program |

## Transformation Details

### Translation
- Use arrow keys to move the cube along X and Y axes
- Use Page Up/Down to move along Z axis

### Rotation
- Use arrow keys to rotate around X and Y axes
- Use Page Up/Down to rotate around Z axis

### Reflection
- Use X, Y, Z keys to toggle reflection across corresponding planes
- Multiple reflections can be combined
- Visually, reflection makes the cube appear mirrored across the specified axis

### Shearing
- Use arrow keys to apply shear along X and Y axes
- Use Page Up/Down to apply shear along Z axis
- Shearing will cause the cube to slant while preserving parallel edges

### Scaling
- Use arrow keys to scale along X and Y axes
- Use Page Up/Down to scale along Z axis
- Values less than 1 shrink the cube, values greater than 1 enlarge it

## Requirements

- C++ compiler
- OpenGL libraries
- GLUT (OpenGL Utility Toolkit)

## Compilation Instructions

### Linux
```bash
# Install required packages (Ubuntu/Debian)
sudo apt-get install freeglut3-dev

# Compile
g++ -o transformation_demo transformation_demo.cpp -lGL -lGLU -lglut

# Run
./transformation_demo
```

### Windows
```bash
# Using MinGW
g++ -o transformation_demo.exe transformation_demo.cpp -lopengl32 -lglu32 -lfreeglut

# Run
transformation_demo.exe
```

### macOS
```bash
# Compile
g++ -o transformation_demo transformation_demo.cpp -framework OpenGL -framework GLUT

# Run
./transformation_demo
```

## Implementation Notes

- The program uses OpenGL's matrix stack for applying transformations
- Reflections are implemented as negative scaling operations
- Shearing is implemented using a custom transformation matrix
- The cube is rendered as a wireframe with colored edges for better visualization of transformations

## Educational Context

This demo is designed to illustrate the concepts discussed in Chapter 5: Transformations of the computer graphics curriculum. It provides a practical visualization of the mathematical transformations described in the textbook.
