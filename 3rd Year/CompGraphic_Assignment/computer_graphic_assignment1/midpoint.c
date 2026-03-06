// SCT211-0504/2021 - Gatmach Yuol Nyuon
// Question: Midpoint Line-Drawing Algorithm
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Draw coordinate system with axes, grid, and labels
void renderCoordinateGrid() {
    // Draw main axes
    glColor3f(0.5, 0.5, 0.5);  // Medium gray for axes
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
    glColor3f(0.2, 0.2, 0.2);  // Darker gray for grid
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
    glColor3f(1.0, 1.0, 1.0);  // White for labels
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

// Calculate and print midpoint line algorithm steps
// Calculate and print midpoint line algorithm steps
void calculateMidpointLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;  // Direction of x
    int sy = (y0 < y1) ? 1 : -1;   // Direction of y

    printf("\nMidpoint Line Algorithm from (%d,%d) to (%d,%d):\n", x0, y0, x1, y1);
    printf("Step 1: Compute dx and dy\n");
    printf("dx = x2 - x1 = %d - %d = %d\n", x1, x0, x1 - x0);
    printf("dy = y2 - y1 = %d - %d = %d\n", y1, y0, y1 - y0);

    // Determine if the line is steep (|dy| > |dx|)
    int steep = dy > dx;

    // Swap dx and dy if the line is steep
    if (steep) {
        int temp = dx;
        dx = dy;
        dy = temp;
    }

    // Compute initial decision parameter
    int p = 2 * dy - dx;

    printf("\nStep 2: Compute Initial Decision Parameter\n");
    printf("P0 = 2*dy - dx = 2*%d - %d = %d\n", dy, dx, p);

    printf("\nStep 3: Iterate to compute pixel positions\n");
    printf("Starting point: (%d, %d), P = %d\n", x0, y0, p);

    int x = x0;
    int y = y0;

    // Iterate until the final point is reached
    while (!(x == x1 && y == y1)) {
        // Plot the current point
        printf("Plot point: (%d, %d), P = %d\n", x, y, p);

        // Update the decision parameter
        if (p > 0) {
            if (steep) {
                x += sx;  // Move in x-direction for steep lines
            } else {
                y += sy;  // Move in y-direction for shallow lines
            }
            p = p - 2 * dx;
        }

        if (steep) {
            y += sy;  // Always move in y-direction for steep lines
        } else {
            x += sx;  // Always move in x-direction for shallow lines
        }

        p = p + 2 * dy;
    }

    // Plot the final point
    printf("Final point: (%d, %d), P = %d\n", x, y, p);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate system
    renderCoordinateGrid();

    // Draw the line from (0,2) to (-1,4)
    glColor3f(0.0, 0.8, 0.2);  // Green color for the line
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2i(0, 2);   // Start point
        glVertex2i(-1, 4);  // End point
    glEnd();

    // Draw endpoints as points
    glColor3f(1.0, 0.0, 0.0);  // Red color for points
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(0, 2);   // Start point
        glVertex2i(-1, 4);  // End point
    glEnd();

    // Draw intermediate points calculated by midpoint algorithm
    glColor3f(1.0, 1.0, 0.0);  // Yellow color for intermediate points
    glPointSize(3.0);
    glBegin(GL_POINTS);
        // These would be the actual points calculated by the algorithm
        glVertex2i(0, 2);
        glVertex2i(0, 3);
        glVertex2i(-1, 4);
    glEnd();

    glFlush();
}

// Initialize OpenGL settings
void initializeGraphics() {
    glClearColor(0.0, 0.0, 0.1, 1.0);  // Dark blue background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);  // Set coordinate system range
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Line Algorithm: (0,2) to (-1,4)");

    glewInit();
    initializeGraphics();

    // Calculate midpoint line algorithm steps
    calculateMidpointLine(0, 2, -1, 4);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}