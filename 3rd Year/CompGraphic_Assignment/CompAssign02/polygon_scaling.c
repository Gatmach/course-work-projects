#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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
    for (int i = -40; i <= 40; i += 1) {
        glVertex2f(i, -40.0);
        glVertex2f(i, 40.0);
    }

    // Draw horizontal grid lines
    for (int i = -40; i <= 40; i += 1) {
        glVertex2f(-40.0, i);
        glVertex2f(40.0, i);
    }

    glEnd();
}

// Function to draw the polygon
void drawPolygon() {
    glColor3f(0.0, 1.0, 0.0); // Green color for the polygon
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
    glVertex2f(-40.0, 0.0);
    glVertex2f(40.0, 0.0); // X-axis
    glVertex2f(0.0, -40.0);
    glVertex2f(0.0, 40.0); // Y-axis
    glEnd();

    // Add axis labels
    renderText(39.5, -0.8, "X");
    renderText(-0.8, 39.5, "Y");

    // Draw coordinate numbers
    for (int i = -40; i <= 40; i += 1) {
        if (i == 0) continue;

        // X-axis labels
        char buffer[10];
        sprintf(buffer, "%d", i);
        renderText(i - 0.2, -1.5, buffer); // Adjust position for X-axis labels

        // Y-axis labels
        renderText(-1.5, i - 0.2, buffer); // Adjust position for Y-axis labels
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the grid
    drawGrid();

    // Draw the axes
    drawAxes();

    // Apply scaling transformation
    glPushMatrix(); // Save the current matrix
    glScalef(2.0, 2.0, 1.0); // Scale up by a factor of 2

    // Draw the scaled polygon
    drawPolygon();

    glPopMatrix(); // Restore the original matrix

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-40, 40, -40, 40); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scaled Polygon with Grid");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}