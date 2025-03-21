#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Global variables
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;
float translationX = 0.0f;
float translationY = 0.0f;
float translationZ = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;
float shearX = 0.0f;
float shearY = 0.0f;
float shearZ = 0.0f;
bool reflectX = false;
bool reflectY = false;
bool reflectZ = false;
int transformationMode = 0; // 0: Translation, 1: Rotation, 2: Reflection, 3: Shearing, 4: Scaling
const char* transformationNames[] = {"Translation", "Rotation", "Reflection", "Shearing", "Scaling"};

// Cube vertices (centered at origin)
GLfloat vertices[][3] = {
    {-0.5f, -0.5f, -0.5f},  // 0
    {0.5f, -0.5f, -0.5f},   // 1
    {0.5f, 0.5f, -0.5f},    // 2
    {-0.5f, 0.5f, -0.5f},   // 3
    {-0.5f, -0.5f, 0.5f},   // 4
    {0.5f, -0.5f, 0.5f},    // 5
    {0.5f, 0.5f, 0.5f},     // 6
    {-0.5f, 0.5f, 0.5f}     // 7
};

// Colors for edges
GLfloat edgeColors[][3] = {
    {1.0f, 0.0f, 0.0f},  // Red
    {0.0f, 1.0f, 0.0f},  // Green
    {0.0f, 0.0f, 1.0f},  // Blue
    {1.0f, 1.0f, 0.0f},  // Yellow
    {1.0f, 0.0f, 1.0f},  // Magenta
    {0.0f, 1.0f, 1.0f},  // Cyan
    {1.0f, 0.5f, 0.0f},  // Orange
    {0.5f, 0.0f, 1.0f},  // Purple
    {0.0f, 0.5f, 0.0f},  // Dark Green
    {0.5f, 0.5f, 1.0f},  // Light Blue
    {1.0f, 0.5f, 0.5f},  // Pink
    {0.5f, 0.5f, 0.5f}   // Gray
};

// Cube edges (pairs of vertex indices)
GLint edges[][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},  // Bottom face
    {4, 5}, {5, 6}, {6, 7}, {7, 4},  // Top face
    {0, 4}, {1, 5}, {2, 6}, {3, 7}   // Connecting edges
};

void reset() {
    // Reset all transformation parameters
    angleX = angleY = angleZ = 0.0f;
    translationX = translationY = translationZ = 0.0f;
    scaleX = scaleY = scaleZ = 1.0f;
    shearX = shearY = shearZ = 0.0f;
    reflectX = reflectY = reflectZ = false;
    glutPostRedisplay();
}

void drawCoordinateSystem() {
    // Draw coordinate axes
    glLineWidth(2.0f);
    
    // X-axis (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    
    // Y-axis (green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();
    
    // Z-axis (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
    
    // Draw small grid on XZ plane
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue; // Skip the axes
        
        // X grid lines
        glVertex3f(i, 0.0f, -10.0f);
        glVertex3f(i, 0.0f, 10.0f);
        
        // Z grid lines
        glVertex3f(-10.0f, 0.0f, i);
        glVertex3f(10.0f, 0.0f, i);
    }
    glEnd();
}

void drawCube() {
    // Apply the current transformation based on mode
    glPushMatrix();
    
    // Apply translation
    glTranslatef(translationX, translationY, translationZ);
    
    // Apply rotation
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    
    // Apply scaling
    glScalef(scaleX, scaleY, scaleZ);
    
    // Apply reflection (as negative scaling)
    if (reflectX) glScalef(-1.0f, 1.0f, 1.0f);
    if (reflectY) glScalef(1.0f, -1.0f, 1.0f);
    if (reflectZ) glScalef(1.0f, 1.0f, -1.0f);
    
    // Apply shearing via custom matrix
    if (shearX != 0.0f || shearY != 0.0f || shearZ != 0.0f) {
        GLfloat shearMatrix[16] = {
            1.0f, shearY, shearZ, 0.0f,
            shearX, 1.0f, shearZ, 0.0f,
            shearX, shearY, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        glMultMatrixf(shearMatrix);
    }

    // Draw the edges with different colors
    glLineWidth(3.0f);
    for (int i = 0; i < 12; i++) {
        glColor3fv(edgeColors[i]);
        glBegin(GL_LINES);
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);
        glEnd();
    }
    
    // Draw vertex points
    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 8; i++) {
        glVertex3fv(vertices[i]);
    }
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set camera position for better viewing
    gluLookAt(3.0f, 3.0f, 6.0f,  // Eye position
              0.0f, 0.0f, 0.0f,  // Look at position
              0.0f, 1.0f, 0.0f); // Up vector
    
    // Draw coordinate system first
    drawCoordinateSystem();
    
    // Then draw the transformed cube
    drawCube();
    
    // Display information about current transformation
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Display text (using GLUT bitmap font)
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    
    std::string modeText = "Mode: " + std::string(transformationNames[transformationMode]);
    for (char c : modeText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    // Display parameters for current transformation mode
    std::string paramText;
    switch (transformationMode) {
        case 0: // Translation
            paramText = "Translation: X=" + std::to_string(translationX) + 
                        ", Y=" + std::to_string(translationY) + 
                        ", Z=" + std::to_string(translationZ);
            break;
        case 1: // Rotation
            paramText = "Rotation: X=" + std::to_string(angleX) + 
                        "°, Y=" + std::to_string(angleY) + 
                        "°, Z=" + std::to_string(angleZ) + "°";
            break;
        case 2: // Reflection
            paramText = "Reflection: X=" + std::string(reflectX ? "ON" : "OFF") + 
                        ", Y=" + std::string(reflectY ? "ON" : "OFF") + 
                        ", Z=" + std::string(reflectZ ? "ON" : "OFF");
            break;
        case 3: // Shearing
            paramText = "Shearing: X=" + std::to_string(shearX) + 
                        ", Y=" + std::to_string(shearY) + 
                        ", Z=" + std::to_string(shearZ);
            break;
        case 4: // Scaling
            paramText = "Scaling: X=" + std::to_string(scaleX) + 
                        ", Y=" + std::to_string(scaleY) + 
                        ", Z=" + std::to_string(scaleZ);
            break;
    }
    
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 40);
    for (char c : paramText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    // Display instructions
    std::string instructions = "Keys: M - Change Mode, R - Reset, Arrow Keys/Page Up/Down - Adjust, X/Y/Z - Select Axis";
    glRasterPos2i(10, 20);
    for (char c : instructions) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    const float step = 0.1f;
    
    switch (key) {
        case 'm':
        case 'M':
            // Change transformation mode
            transformationMode = (transformationMode + 1) % 5;
            break;
        
        case 'r':
        case 'R':
            // Reset all transformations
            reset();
            break;
        
        case 'x':
        case 'X':
            // Toggle reflection along X-axis
            if (transformationMode == 2) {
                reflectX = !reflectX;
            }
            break;
        
        case 'y':
        case 'Y':
            // Toggle reflection along Y-axis
            if (transformationMode == 2) {
                reflectY = !reflectY;
            }
            break;
        
        case 'z':
        case 'Z':
            // Toggle reflection along Z-axis
            if (transformationMode == 2) {
                reflectZ = !reflectZ;
            }
            break;
        
        case 27: // ESC key
            exit(0);
            break;
    }
    
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    const float translationStep = 0.1f;
    const float rotationStep = 5.0f;
    const float scaleStep = 0.1f;
    const float shearStep = 0.1f;
    
    switch (key) {
        case GLUT_KEY_LEFT:
            switch (transformationMode) {
                case 0: translationX -= translationStep; break;
                case 1: angleY -= rotationStep; break;
                case 3: shearX -= shearStep; break;
                case 4: scaleX -= scaleStep; break;
            }
            break;
        
        case GLUT_KEY_RIGHT:
            switch (transformationMode) {
                case 0: translationX += translationStep; break;
                case 1: angleY += rotationStep; break;
                case 3: shearX += shearStep; break;
                case 4: scaleX += scaleStep; break;
            }
            break;
        
        case GLUT_KEY_UP:
            switch (transformationMode) {
                case 0: translationY += translationStep; break;
                case 1: angleX -= rotationStep; break;
                case 3: shearY += shearStep; break;
                case 4: scaleY += scaleStep; break;
            }
            break;
        
        case GLUT_KEY_DOWN:
            switch (transformationMode) {
                case 0: translationY -= translationStep; break;
                case 1: angleX += rotationStep; break;
                case 3: shearY -= shearStep; break;
                case 4: scaleY -= scaleStep; break;
            }
            break;
        
        case GLUT_KEY_PAGE_UP:
            switch (transformationMode) {
                case 0: translationZ += translationStep; break;
                case 1: angleZ += rotationStep; break;
                case 3: shearZ += shearStep; break;
                case 4: scaleZ += scaleStep; break;
            }
            break;
        
        case GLUT_KEY_PAGE_DOWN:
            switch (transformationMode) {
                case 0: translationZ -= translationStep; break;
                case 1: angleZ -= rotationStep; break;
                case 3: shearZ -= shearStep; break;
                case 4: scaleZ -= scaleStep; break;
            }
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Transformation Demo");
    
    // Set up OpenGL state
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    glutMainLoop();
    return 0;
}
