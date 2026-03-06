
#include <GL/freeglut.h>
#include <stdio.h>

// Scaling factor
#define SCALE 2.0

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw Cartesian plane with grid and small ticks
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);  // Light gray grid lines
    for (int i = -24; i <= 24; i++) {  // Adjusted for scaling
        glBegin(GL_LINES);
        glVertex2i(i, -24); glVertex2i(i, 24);  // Vertical lines
        glVertex2i(-24, i); glVertex2i(24, i);  // Horizontal lines
        glEnd();
    }

    // Axes (white)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-24, 0); glVertex2i(24, 0);  // X-axis
    glVertex2i(0, -24); glVertex2i(0, 24);  // Y-axis
    glEnd();

    // Labels for grid numbers
    glColor3f(1.0, 1.0, 1.0);
    char label[10];
    for (int i = -24; i <= 24; i += 4) {  // Adjusted for clarity
        if (i != 0) {
            sprintf(label, "%d", i);
            drawText(i - 0.3, -0.5, label);  // X-axis labels
            drawText(-0.7, i - 0.3, label);  // Y-axis labels
        }
    }

    drawText(-0.3, -0.5, "0");  // Origin
    drawText(23.5, -0.5, "X");  // X-axis title
    drawText(-0.5, 23.5, "Y");  // Y-axis title
}

// Function to draw the scaled polygon
void drawScaledPolygon() {
    glColor3f(0.0, 1.0, 1.0);  // Light blue for scaled polygon
    glBegin(GL_POLYGON);
    glVertex2i(8 * SCALE, 4 * SCALE);
    glVertex2i(2 * SCALE, 4 * SCALE);
    glVertex2i(0 * SCALE, 8 * SCALE);
    glVertex2i(3 * SCALE, 12 * SCALE);
    glVertex2i(7 * SCALE, 12 * SCALE);
    glVertex2i(10 * SCALE, 8 * SCALE);
    glEnd();

    // Labeling the new scaled vertices
    drawText(16, 8, "(16,8)");
    drawText(4, 8, "(4,8)");
    drawText(0, 16, "(0,16)");
    drawText(6, 24, "(6,24)");
    drawText(14, 24, "(14,24)");
    drawText(20, 16, "(20,16)");
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawScaledPolygon();
    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-25, 25, -25, 25);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Q4aii: Scaled Polygon");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

