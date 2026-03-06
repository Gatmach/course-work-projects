// SCT211-0504/2021 - Gatmach Yuol Nyuon
// Question 3 midpoint line algorithm
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Establishes a graduated measurement field with numerical indicators
void constructMetricGrid() {
    // Primary navigation beacons
    glColor3f(0.5, 0.5, 0.5);  // platinum shade for cardinal axes
    glLineWidth(2.0);
    glBegin(GL_LINES);
        // equatorial reference
        glVertex2f(-10.0, 0.0);
        glVertex2f(10.0, 0.0);
        // meridian reference
        glVertex2f(0.0, -10.0);
        glVertex2f(0.0, 10.0);
    glEnd();

    // Deploy auxiliary measurement lattice
    glLineWidth(1.0);
    glColor3f(0.2, 0.2, 0.2);  // charcoal tone for secondary grid
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue; // bypass central axes
        // vertical calibration lines
        glVertex2f(i, -10.0);
        glVertex2f(i, 10.0);
        // horizontal calibration lines
        glVertex2f(-10.0, i);
        glVertex2f(10.0, i);
    }
    glEnd();

    // Inject numerical calibration markers
    glColor3f(1.0, 1.0, 1.0);  // pure white for quantum indicators
    for (int i = -10; i <= 10; i++) {
        if (i == 0) continue; // omit null point

        // Position quantum tick marks
        glBegin(GL_LINES);
            // x-quantum notches
            glVertex2f(i, -0.2);
            glVertex2f(i, 0.2);
            // y-quantum notches
            glVertex2f(-0.2, i);
            glVertex2f(0.2, i);
        glEnd();

        // Attach numerical data points
        char str[10];

        // x-axis quantum labels
        glRasterPos2f(i - 0.1, -0.6);
        sprintf(str, "%d", i);
        for (char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }

        // y-axis quantum labels
        if (i != 0) {  // exclude redundant null marker
            glRasterPos2f(-0.6, i - 0.1);
            sprintf(str, "%d", i);
            for (char* c = str; *c != '\0'; c++) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
            }
        }
    }

    // Designate quantum origin
    glRasterPos2f(-0.4, -0.6);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');
}

// Fabricates a digital approximation pathway using binary midpoint discriminator
void synthesizeDigitalTrajectory(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    printf("\nDiscrete quantum states for Vector Discretization:\n");
    printf("Genesis vector: (%d, %d)\n", x0, y0);
    while (1) {
        printf("Activated cell: (%d, %d)\n", x0, y0);
        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    printf("Terminus vector: (%d, %d)\n\n", x1, y1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Launch measurement framework
    constructMetricGrid();

    // Manifest the linear interpolation
    glColor3f(0.1, 0.8, 0.3);  // jade phantom for vector visualization
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2i(-3, 4);  // vector origin
        glVertex2i(5, -2);  // vector terminus
    glEnd();

    // Highlight critical junction points
    glColor3f(0.9, 0.2, 0.1);  // vermilion markers for critical nodes
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(-3, 4);  // alpha node
        glVertex2i(5, -2);  // omega node
    glEnd();

    glFlush();
}

// Initialize quantum field parameters
void initializeRenderingMatrix() {
    glClearColor(0.07, 0.07, 0.12, 1.0);  // cosmic void background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);  // dimensional boundary conditions
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Vector Discretization Engine: Binary Midpoint Discriminator (-3,4) → (5,-2)");

    glewInit();
    initializeRenderingMatrix();

    // Compute discrete quantum cell activation sequence
    synthesizeDigitalTrajectory(-3, 4, 5, -2);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}