// Gatmach Yuol Nyuon
// SCT211-0504/2021
// Program to draw a circle using Bresenham's algorithm and rotate it by 60 degrees
// Question 1 (a)
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constants
const int PIXELS_PER_CM = 10;  // Scale factor: 10 pixels = 1 cm
const int radius = 4 * PIXELS_PER_CM;  // 4 cm converted to pixels
const int centerX = 1 * PIXELS_PER_CM;  // 1 cm converted to pixels
const int centerY = 1 * PIXELS_PER_CM;  // 1 cm converted to pixels

void plot(int x, int y) {
    glVertex2i(x, y);
}

void drawBresenhamCircle(int xCenter, int yCenter, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    
    glBegin(GL_POINTS);
    while (x <= y) {
        // Plot points in all 8 octants
        plot(xCenter + x, yCenter + y);
        plot(xCenter - x, yCenter + y);
        plot(xCenter + x, yCenter - y);
        plot(xCenter - x, yCenter - y);
        plot(xCenter + y, yCenter + x);
        plot(xCenter - y, yCenter + x);
        plot(xCenter + y, yCenter - x);
        plot(xCenter - y, yCenter - x);

        // Update decision parameter and coordinates
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-100.0, 0.0);
        glVertex2f(100.0, 0.0);
        glVertex2f(0.0, -100.0);
        glVertex2f(0.0, 100.0);
    glEnd();

    // Label axes
    glColor3f(0.0, 0.0, 0.0);
    for (int i = -100; i <= 100; i += 10) {
        if (i == 0) continue;
        char str[10];
        sprintf(str, "%d", i / 10);
        glRasterPos2f(i - 2, -5);
        for (char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
        glRasterPos2f(-7, i - 2);
        for (char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
    }
}

void drawGrid() {
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    for(int i = -100; i <= 100; i += 10) {
        if(i == 0) continue;
        glVertex2f(i, -100.0);
        glVertex2f(i, 100.0);
        glVertex2f(-100.0, i);
        glVertex2f(100.0, i);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw background
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-100, -100);
        glVertex2f(100, -100);
        glVertex2f(100, 100);
        glVertex2f(-100, 100);
    glEnd();
    
    // Draw grid and axes
    drawGrid();
    drawAxes();
    
    // Draw the circle using Bresenham algorithm
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    drawBresenhamCircle(centerX, centerY, radius);
    
    // Mark the center point
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
        glVertex2i(centerX, centerY);
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle at (1,1) with radius 4cm");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}