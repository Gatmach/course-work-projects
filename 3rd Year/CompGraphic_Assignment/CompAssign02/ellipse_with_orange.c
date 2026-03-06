// Gatmach Yuol Nyuon
// SCT211-0504/2021
// Program to draw an ellipse using smooth parametric approach
// Question 2 a (i)
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// Define the ellipse parameters
const int a = 6, b = 5;           // a=6, b=5 from the equation
const int centerX = 2, centerY = -1;  // Center at (2,-1) based on the equation

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to check if a point is inside the ellipse
bool isInsideEllipse(float x, float y) {
    float term1 = pow(x - centerX, 2) / (a * a);
    float term2 = pow(y - centerY, 2) / (b * b);
    return (term1 + term2) <= 1.0;
}

// Function to draw the Cartesian plane with gray grid
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);  // Light gray grid lines
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);
        glVertex2i(-12, i); glVertex2i(12, i);
        glEnd();
    }

    // Axes (white)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-12, 0); glVertex2i(12, 0);  // X-axis
    glVertex2i(0, -12); glVertex2i(0, 12);  // Y-axis
    glEnd();

    // Unit ticks (white)
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);
        glVertex2f(-0.1, i); glVertex2f(0.1, i);
        glEnd();
    }

    // Labels for grid numbers
    glColor3f(1.0, 1.0, 1.0);
    char label[10];
    for (int i = -12; i <= 12; i++) {
        if (i != 0) {
            sprintf(label, "%d", i);
            drawText(i - 0.3, -0.5, label);  // X-axis labels
            drawText(-0.7, i - 0.3, label);  // Y-axis labels
        }
    }

    drawText(-0.3, -0.5, "0");  // Origin
    drawText(11.5, -0.5, "X");  // X-axis title
    drawText(-0.5, 11.5, "Y");  // Y-axis title
    
    // Highlight the center point (2,-1)
    glColor3f(0.0, 0.0, 1.0); // Blue for center point
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(centerX, centerY);
    glEnd();
    glPointSize(1.0);
    
    // Label the center point
    char centerLabel[20];
    sprintf(centerLabel, "(%d,%d)", centerX, centerY);
    drawText(centerX + 0.2, centerY + 0.2, centerLabel);
}

// Function to draw the ellipse using smooth parametric approach
void drawSmoothEllipse() {
    // Draw using parametric equation
    glBegin(GL_LINE_LOOP);
    for (float t = 0; t < 2 * M_PI; t += 0.01) {
        float x = centerX + a * cos(t);
        float y = centerY + b * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to display equation on screen
void displayEquation() {
    glColor3f(1.0, 1.0, 1.0);  // White text
    drawText(-11.5, 11.5, "Ellipse: ((x-2)^2/36) + ((y+1)^2/25) = 1");
}

// Flood fill the ellipse using OpenGL's polygon capabilities
void floodFillEllipse() {
    // Orange color #FFA500 in RGB (255, 165, 0)
    glColor3f(1.0f, 0.65f, 0.0f);
    
    // Use OpenGL's built-in polygon filling
    glBegin(GL_POLYGON);
    for (float t = 0; t < 2 * M_PI; t += 0.01) {
        float x = centerX + a * cos(t);
        float y = centerY + b * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawCartesianPlane();
    
    // Display the equation
    displayEquation();
    
    // First fill the ellipse with orange color
    floodFillEllipse();
    
    // Then draw the ellipse boundary
    glColor3f(1.0, 0.0, 0.0); // Red color for the ellipse boundary
    glLineWidth(2.0);
    drawSmoothEllipse();
    glLineWidth(1.0);
    
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12.5, 12.5, -12.5, 12.5);  // Match the Cartesian plane range
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Orange Filled Ellipse: ((x-2)^2/36) + ((y+1)^2/25) = 1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}