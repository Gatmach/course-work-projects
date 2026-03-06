// Gatmach Yuol Nyuon
// SCT211-0504/2021

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Function to draw the coordinate system with axes, grid, and labels
void drawCoordinateSystem() {
    // Draw main axes
    glColor3f(0.5, 0.5, 0.5); 
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
    glColor3f(0.2, 0.2, 0.2);  // Grid color
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue; 
        // Vertical lines
        glVertex2f(i, -10.0);
        glVertex2f(i, 10.0);
        // Horizontal lines
        glVertex2f(-10.0, i);
        glVertex2f(10.0, i);
    }
    glEnd();

    // Draw tick marks and axis labels
    glColor3f(1.0, 1.0, 1.0); 
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue;

        // Draw tick marks
        glBegin(GL_LINES);
            // X-axis tick marks
            glVertex2f(i, -0.2);
            glVertex2f(i, 0.2);
            // Y-axis tick marks
            glVertex2f(-0.2, i);
            glVertex2f(0.2, i);
        glEnd();

        // Draw numerical labels
        char str[10];

        // X-axis labels
        glRasterPos2f(i - 0.1, -0.6);
        sprintf(str, "%d", i);
        for (char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }

        // Y-axis labels
        if (i != 0) {  // Skip 0 for y-axis
            glRasterPos2f(-0.6, i - 0.1);
            sprintf(str, "%d", i);
            for (char* c = str; *c != '\0'; c++) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
            }
        }
    }

    // Draw origin label "0"
    glRasterPos2f(-0.4, -0.6);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
}

// Function to compute and display intermediate points using Xiaolin Wu's Algorithm
void computeIntermediatePoints(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    int steep = abs(dy) > abs(dx);

    // Swap x and y if the line is steep
    if (steep) {
        int temp = x0; x0 = y0; y0 = temp;
        temp = x1; x1 = y1; y1 = temp;
    }

    // Ensure the line is drawn from left to right
    if (x0 > x1) {
        int temp = x0; x0 = x1; x1 = temp;
        temp = y0; y0 = y1; y1 = temp;
    }

    dx = x1 - x0;
    dy = y1 - y0;
    float gradient = dx == 0 ? 1 : (float)dy / dx;  // Avoid division by zero

    float y = y0 + gradient;
    printf("\nComputed Intermediate Points for Xiaolin Wu's Algorithm:\n");
    printf("Start Point: (%d, %d)\n", x0, y0);
    
    // Compute and print intermediate points
    for (int x = x0 + 1; x < x1; x++) {
        printf("Point: (%d, %d)\n", steep ? (int)y : x, steep ? x : (int)y);
        y += gradient;
    }

    // Print the final end point
    printf("End Point: (%d, %d)\n\n", steep ? y1 : x1, steep ? x1 : y1);
}

// Function to handle OpenGL display rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate system
    drawCoordinateSystem();

    // Draw the line using OpenGL (green color)
    glColor3f(0.0, 1.0, 0.0);  
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2i(1, 1);  // Start point
        glVertex2i(3, 5);  // End point
    glEnd();

    // Highlight endpoints using yellow color
    glColor3f(1.0, 1.0, 0.0);  // Yellow color
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(1, 1);  // Start point
        glVertex2i(3, 5);  // End point
    glEnd();

    glFlush();

}

// OpenGL initialization function
void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0);  // Set background color to gray
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);  // Define coordinate system range
}

// Main function to initialize OpenGL and start the program
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Xiaolin Wu's Line Algorithm");

    glewInit();
    init();

    // Compute and print intermediate points for verification
    computeIntermediatePoints(1, 1, 3, 5);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
