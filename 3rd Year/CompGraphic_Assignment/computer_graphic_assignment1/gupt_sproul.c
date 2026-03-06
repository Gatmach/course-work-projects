// Gatmach Yuol Nyuon
// SCT211-0504/2021
// gupt_sproull.c 
// draw points from (-2,3) to (1,4)
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


void drawCoordinateSystem() {
    // draw main axes
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

    // grid lines
    glLineWidth(1.0);
    glColor3f(0.2, 0.2, 0.2);  // Darker gray for grid
    glBegin(GL_LINES);
    for(int i = -10; i <= 10; i++) {
        if(i == 0) continue; // Skip the axes
        // Vertical lines
        glVertex2f(i, -10.0);
        glVertex2f(i, 10.0);
        // Horizontal lines
        glVertex2f(-10.0, i);
        glVertex2f(10.0, i);
    }
    glEnd();

    // draw tick marks and numbers
    glColor3f(1.0, 1.0, 1.0);  // White color for numbers
    for(int i = -10; i <= 10; i++) {
        if(i == 0) continue; // Skip origin
        
        // draw tick marks
        glBegin(GL_LINES);
            // X-axis ticks
            glVertex2f(i, -0.2);
            glVertex2f(i, 0.2);
            // Y-axis ticks
            glVertex2f(-0.2, i);
            glVertex2f(0.2, i);
        glEnd();

        // draw numbers
        char str[10];
        
        // x-axis numbers
        glRasterPos2f(i - 0.1, -0.6);
        sprintf(str, "%d", i);
        for(char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
        
        // y-axis numbers
        if(i != 0) {  // Skip 0 for y-axis
            glRasterPos2f(-0.6, i - 0.1);
            sprintf(str, "%d", i);
            for(char* c = str; *c != '\0'; c++) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
            }
        }
    }

    // draw origin "0"
    glRasterPos2f(-0.4, -0.6);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
}

void computeAndPrintPoints(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    // printf("\nIntermediate points for Gupta-Sproull Algorithm:\n");
    printf("Starting and end points: (%d, %d) and (%d, %d)\n", x0, y0, x1, y1);
    while (1) {
        printf("Point: (%d, %d)\n", x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // draw coordinate system
    drawCoordinateSystem();

    // draw the line in blue
    glColor3f(0.0, 0.5, 1.0);
    glLineWidth(2.0);  // line width
    glBegin(GL_LINES);
        glVertex2i(-2, 3); // start point
        glVertex2i(1, 4);  // end point
    glEnd();

    // draw endpoints as points
    glColor3f(1.0, 0.0, 0.0);  // Red color for points
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(-2, 3); // start point
        glVertex2i(1, 4);  // end point
    glEnd();

    glFlush();
}

void init() {
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
    glutCreateWindow("Gupta-Sproull Algorithm");

    glewInit();
    init();

    // compute and print points before entering the main loop
    computeAndPrintPoints(-2, 3, 1, 4);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}