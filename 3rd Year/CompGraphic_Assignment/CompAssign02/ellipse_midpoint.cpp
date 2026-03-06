//Gatmach Yuol Nyuon
//SCT211-0504/2021
//Program to draw an ellipse using smooth parametric approach
// Question 2 a)
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <vector>

// Define the ellipse parameters
// For equation ((x-h)^2/a^2) + ((y-k)^2/b^2) = 1
// where center is at (h,k)
const int a = 6, b = 5;           // a=6, b=5 from the equation
const int centerX = 2, centerY = -1;  // Center at (2,-1) based on the equation

// Structure to store points
struct Point {
    float x, y;
    Point(float _x, float _y) : x(_x), y(_y) {}
};

// Helper function for rendering text
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    }
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

// Draw Axes with labels
void drawAxes() {
    // Draw X and Y axes
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-20.0, 0.0);
    glVertex2f(20.0, 0.0);
    glVertex2f(0.0, -20.0);
    glVertex2f(0.0, 20.0);
    glEnd();
    
    // Add axis labels
    renderText(19.5, -0.8, "X");
    renderText(-0.8, 19.5, "Y");
    
    // Draw coordinate numbers
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue;
        
        // X-axis labels
        char buffer[10];
        sprintf(buffer, "%d", i);
        renderText(i, -0.5, buffer);
        
        // Y-axis labels
        renderText(-0.7, i, buffer);
    }
    
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
    renderText(centerX + 0.2, centerY + 0.2, centerLabel);
}

// Draw Grid
void drawGrid() {
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(0.5);
    glBegin(GL_LINES);
    for (int i = -20; i <= 20; i += 1) {
        if (i == 0) continue;
        glVertex2f(i, -20.0);
        glVertex2f(i, 20.0);
        glVertex2f(-20.0, i);
        glVertex2f(20.0, i);
    }
    glEnd();
}

// Function to display equation on screen
void displayEquation() {
    glColor3f(0.0, 0.0, 0.0);
    renderText(-9.5, 9.5, "Ellipse: ((x-2)^2/36) + ((y+1)^2/25) = 1");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawGrid();
    drawAxes();
    
    // Display the equation
    displayEquation();
    
    // Draw the ellipse
    glColor3f(1.0, 0.0, 0.0); // Red color for the ellipse boundary
    glLineWidth(2.0);
    drawSmoothEllipse();
    glLineWidth(1.0);
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Smooth Ellipse: ((x-2)^2/36) + ((y+1)^2/25) = 1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}