// Gatmach Yuol Nyuon
// SCT211-0504/2021
// Program to draw a circle using Bresenham's algorithm and rotate it by 60 degrees
// Question 1 a (i)
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int radius = 40;  // 4 cm assuming 10 pixels per cm
const int startX = 10, startY = 10;  // Changed to (1,1) in your coordinate system (10 pixels per unit)
const float rotationAngle = -60.0f; // Clockwise rotation

void plot(int x, int y) {
    glVertex2i(x, y);
}

void drawBresenhamCircle(int xCenter, int yCenter, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    glBegin(GL_POINTS);
    while (x <= y) {
        plot(xCenter + x, yCenter + y);
        plot(xCenter - x, yCenter + y);
        plot(xCenter + x, yCenter - y);
        plot(xCenter - x, yCenter - y);
        plot(xCenter + y, yCenter + x);
        plot(xCenter - y, yCenter + x);
        plot(xCenter + y, yCenter - x);
        plot(xCenter - y, yCenter - x);

        if (d < 0)
            d += 4 * x + 6;
        else {
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
    glColor3f(0.6, 0.6, 0.6);
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

void drawRotatedFilledCircle() {
    glPushMatrix();
    glTranslatef(startX, startY, 0);
    glRotatef(rotationAngle, 0, 0, 1);
    glTranslatef(-startX, -startY, 0);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(startX, startY);
    for (int angle = 0; angle <= 360; angle++) {
        float rad = angle * M_PI / 180.0;
        glVertex2f(startX + radius * cos(rad), startY + radius * sin(rad));
    }
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
    glVertex2f(-100, -100);
    glVertex2f(100, -100);
    glVertex2f(100, 100);
    glVertex2f(-100, 100);
    glEnd();
    
    drawGrid();
    drawAxes();
    drawRotatedFilledCircle();
    glFlush();
}

void init() {
    glClearColor(0.7, 0.7, 0.7, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating a circle at 60 degree");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}