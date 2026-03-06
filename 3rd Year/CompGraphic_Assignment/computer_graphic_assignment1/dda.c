// Gatmach Yuol Nyuon
//SCT211-0504/2021
// DIGITAL DIFFERENTIAL ANALYZER
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Function to draw the coordinate system with axes, grid, and labels
void renderCoordinateAxesAndGrid() {
    // Draw main axes
    glColor3f(0.5, 0.5, 0.5);  // Gray color for axes
    glLineWidth(2.0);
    glBegin(GL_LINES);
        // X-axis
        glVertex2f(-10.0, 0.0);
        glVertex2f(10.0, 0.0);
        // Y-axis
        glVertex2f(0.0, -10.0);
        glVertex2f(0.0, 10.0);
    glEnd();

    // Draw grid lines
    glLineWidth(1.0);
    glColor3f(0.2, 0.2, 0.2);  // Dark gray for grid
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue; // Skip the axes
        // Vertical grid lines
        glVertex2f(i, -10.0);
        glVertex2f(i, 10.0);
        // Horizontal grid lines
        glVertex2f(-10.0, i);
        glVertex2f(10.0, i);
    }
    glEnd();

    // Draw tick marks and numbers
    glColor3f(1.0, 1.0, 1.0);  // White color for labels
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue; // Skip origin

        // Draw tick marks
        glBegin(GL_LINES);
            // X-axis ticks
            glVertex2f(i, -0.2);
            glVertex2f(i, 0.2);
            // Y-axis ticks
            glVertex2f(-0.2, i);
            glVertex2f(0.2, i);
        glEnd();

        // Draw coordinate numbers
        char str[10];

        // X-axis numbers
        glRasterPos2f(i - 0.1, -0.6);
        sprintf(str, "%d", i);
        for (char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }

        // Y-axis numbers
        if (i != 0) {  // Skip 0 for y-axis
            glRasterPos2f(-0.6, i - 0.1);
            sprintf(str, "%d", i);
            for (char* c = str; *c != '\0'; c++) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
            }
        }
    }

    // Draw origin "0"
    glRasterPos2f(-0.4, -0.6);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
}

// Function to compute and print intermediate points using DDA algorithm
void calculateDDAPoints(int startX, int startY, int endX, int endY) {
    int dx = endX - startX, dy = endY - startY, steps;
    float xIncrement, yIncrement, x = startX, y = startY;

    // Determine the number of steps
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // Calculate increments for x and y
    xIncrement = dx / (float)steps;
    yIncrement = dy / (float)steps;

    // Print intermediate points
    printf("\nIntermediate points for DDA Algorithm:\n");
    printf("Starting point: (%d, %d)\n", startX, startY);
    for (int i = 0; i <= steps; i++) {
        printf("Point: (%d, %d)\n", (int)round(x), (int)round(y));
        x += xIncrement;
        y += yIncrement;
    }
    printf("Ending point: (%d, %d)\n\n", endX, endY);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    renderCoordinateAxesAndGrid();

    // Draw the line in green
    glColor3f(0.0, 1.0, 0.0); 
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2i(5, 2);  
        glVertex2i(10, 3);  
    glEnd();

    // Draw endpoints as points
    glColor3f(1.0, 0.0, 0.0); 
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(5, 2); 
        glVertex2i(10, 3); 
    glEnd();

    glFlush();
}


void initializeOpenGLSettings() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line-Drawing Algorithm (Unique Version)");

    glewInit();
    initializeOpenGLSettings();

    // Compute and print intermediate points
    calculateDDAPoints(5, 2, 10, 3);

    glutDisplayFunc(renderScene);
    glutMainLoop();
    return 0;
}