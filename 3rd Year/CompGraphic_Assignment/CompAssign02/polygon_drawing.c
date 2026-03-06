#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>

// Define the polygon vertices
const float polygonVertices[6][2] = {
    {8.0, 4.0},  // Vertex 1
    {2.0, 4.0},  // Vertex 2
    {0.0, 8.0},  // Vertex 3
    {3.0, 12.0}, // Vertex 4
    {7.0, 12.0}, // Vertex 5
    {10.0, 8.0}  // Vertex 6
};

// Helper function for rendering text
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    }
}

// Function to draw the grid
void drawGrid() {
    glColor3f(0.5, 0.5, 0.5); // Gray color for the grid
    glLineWidth(0.5);
    glBegin(GL_LINES);

    // Draw vertical grid lines
    for (int i = -20; i <= 20; i += 1) {
        glVertex2f(i, -20.0);
        glVertex2f(i, 20.0);
    }

    // Draw horizontal grid lines
    for (int i = -20; i <= 20; i += 1) {
        glVertex2f(-20.0, i);
        glVertex2f(20.0, i);
    }

    glEnd();
}

// Function to draw the polygon
void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0); // Red color for the polygon
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) {
        glVertex2f(polygonVertices[i][0], polygonVertices[i][1]);
    }
    glEnd();
}

// Function to draw the axes
void drawAxes() {
    // Draw X and Y axes
    glColor3f(0.0, 0.0, 0.0); // Black color for axes
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-20.0, 0.0);
    glVertex2f(20.0, 0.0); // X-axis
    glVertex2f(0.0, -20.0);
    glVertex2f(0.0, 20.0); // Y-axis
    glEnd();

    // Add axis labels
    renderText(19.5, -0.8, "X");
    renderText(-0.8, 19.5, "Y");

    // Draw coordinate numbers
    for (int i = -20; i <= 20; i += 1) {
        if (i == 0) continue;

        // X-axis labels
        char buffer[10];
        sprintf(buffer, "%d", i);
        renderText(i, -0.5, buffer);

        // Y-axis labels
        renderText(-0.7, i, buffer);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the grid
    drawGrid();

    // Draw the axes
    drawAxes();

    // Draw the polygon
    drawPolygon();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -20, 20); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Filled Polygon with Grid");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}