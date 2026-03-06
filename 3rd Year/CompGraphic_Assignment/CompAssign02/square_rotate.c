
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw Cartesian plane with grid and small ticks
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);  // Light gray grid lines
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);  // Vertical lines
        glVertex2i(-12, i); glVertex2i(12, i);  // Horizontal lines
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
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);  // X-axis ticks
        glVertex2f(-0.1, i); glVertex2f(0.1, i);  // Y-axis ticks
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
}

// Function to rotate a point around the origin
void rotatePoint(float x, float y, float angle, float *x_new, float *y_new) {
    float rad = DEG_TO_RAD(angle);
    *x_new = x * cos(rad) - y * sin(rad);
    *y_new = x * sin(rad) + y * cos(rad);
}

// Function to draw the original translated square
void drawTranslatedSquare() {
    glColor3f(1.0, 0.0, 0.0);  // Red for the translated square
    glBegin(GL_LINE_LOOP);
    glVertex2i(2, 6);  // A'
    glVertex2i(6, 6);  // B'
    glVertex2i(6, 2);  // C'
    glVertex2i(2, 2);  // D'
    glEnd();

    // Labeling translated vertices
    drawText(2, 6, "A'(2,6)");
    drawText(6, 6, "B'(6,6)");
    drawText(6, 2, "C'(6,2)");
    drawText(2, 2, "D'(2,2)");
}

// Function to draw the rotated square
void drawRotatedSquare() {
    float angle = 55.0;  // Rotation angle in degrees
    float ax, ay, bx, by, cx, cy, dx, dy;

    // Original translated vertices
    float orig[4][2] = {{2, 6}, {6, 6}, {6, 2}, {2, 2}};
    float rotated[4][2];

    // Rotate each vertex
    for (int i = 0; i < 4; i++) {
        rotatePoint(orig[i][0], orig[i][1], angle, &rotated[i][0], &rotated[i][1]);
    }

    // Draw rotated square
    glColor3f(0.0, 1.0, 1.0);  // Light blue for rotated square
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(rotated[i][0], rotated[i][1]);
    }
    glEnd();

    // Label rotated vertices
    drawText(rotated[0][0], rotated[0][1], "A''");
    drawText(rotated[1][0], rotated[1][1], "B''");
    drawText(rotated[2][0], rotated[2][1], "C''");
    drawText(rotated[3][0], rotated[3][1], "D''");
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawTranslatedSquare();
    drawRotatedSquare();
    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12.5, 12.5, -12.5, 12.5);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Q3aii: Rotated Square");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

