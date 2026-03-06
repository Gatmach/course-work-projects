#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define BUFFER_SIZE 20
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global variables for circumcircle
float circ_x = 0, circ_y = 0, circ_r = 0;

// Function to draw text on screen
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Dynamic grid drawing based on visible area
void drawCartesianPlane() {
    // Calculate grid bounds from circle parameters
    int min_x = floor(circ_x - circ_r) - 5;
    int max_x = ceil(circ_x + circ_r) + 5;
    int min_y = floor(circ_y - circ_r) - 5;
    int max_y = ceil(circ_y + circ_r) + 5;

    // Grid lines (light gray)
    glColor3f(0.15, 0.15, 0.15);
    for (int i = min_x; i <= max_x; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, min_y); glVertex2i(i, max_y);
        glEnd();
    }
    for (int i = min_y; i <= max_y; i++) {
        glBegin(GL_LINES);
        glVertex2i(min_x, i); glVertex2i(max_x, i);
        glEnd();
    }

    // Axes (white)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(min_x, 0); glVertex2i(max_x, 0);  // X-axis
    glVertex2i(0, min_y); glVertex2i(0, max_y);  // Y-axis
    glEnd();

    // Label the axes with numbers
    glColor3f(1.0, 1.0, 1.0); // White color for labels

    // X-axis labels
    for (int i = min_x; i <= max_x; i++) {
        if (i != 0) { // Skip labeling the origin (0, 0)
            char label[BUFFER_SIZE];
            snprintf(label, BUFFER_SIZE, "%d", i);
            drawText(i - 0.1, -0.5, label); // Label below the tick
        }
    }

    // Y-axis labels
    for (int i = min_y; i <= max_y; i++) {
        if (i != 0) { // Skip labeling the origin (0, 0)
            char label[BUFFER_SIZE];
            snprintf(label, BUFFER_SIZE, "%d", i);
            drawText(0.5, i - 0.1, label); // Label to the left of the tick
        }
    }

    // Label the origin (0, 0)
    drawText(0.1, 0.1, "0");
}

void drawTriangle() {
    glColor3f(0.0, 1.0, 0.0);  // Green color
    glBegin(GL_TRIANGLES);
    glVertex2f(-1, 6);
    glVertex2f(2, 0);
    glVertex2f(-4, 9);
    glEnd();
}

void computeCircumcircle(float x1, float y1,
    float x2, float y2,
    float x3, float y3) {
    float D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

    circ_x = ((x1 * x1 + y1 * y1) * (y2 - y3)
        + (x2 * x2 + y2 * y2) * (y3 - y1)
        + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;

    circ_y = ((x1 * x1 + y1 * y1) * (x3 - x2)
        + (x2 * x2 + y2 * y2) * (x1 - x3)
        + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;

    circ_r = sqrt(pow(x1 - circ_x, 2) + pow(y1 - circ_y, 2));
}

void drawCircumscribedCircle() {
    glColor3f(1.0, 0.0, 0.0);  // Red color
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        float x = circ_x + circ_r * cos(angle);
        float y = circ_y + circ_r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawTriangle();
    drawCircumscribedCircle();

    // Label circumcenter
    char label[BUFFER_SIZE];
    snprintf(label, BUFFER_SIZE, "(%.2f, %.2f)", circ_x, circ_y);
    drawText(circ_x, circ_y, label);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Triangle vertices
    float ax = -1, ay = 6;
    float bx = 2, by = 0;
    float cx = -4, cy = 9;

    // Calculate circumcircle
    computeCircumcircle(ax, ay, bx, by, cx, cy);

    // Set dynamic viewport
    float padding = circ_r * 0.2;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(circ_x - circ_r - padding,
        circ_x + circ_r + padding,
        circ_y - circ_r - padding,
        circ_y + circ_r + padding);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Properly Scaled Circumscribed Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}