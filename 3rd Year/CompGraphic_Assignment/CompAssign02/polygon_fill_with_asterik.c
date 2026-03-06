#include <GL/freeglut.h>
#include <stdio.h>

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw the Cartesian plane (unchanged)
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
}

// Function to draw the polygon outline and label vertices
void drawPolygon() {
    glColor3f(1.0, 1.0, 0.0);  // Yellow outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(8, 4);
    glVertex2i(2, 4);
    glVertex2i(0, 8);
    glVertex2i(3, 12);
    glVertex2i(7, 12);
    glVertex2i(10, 8);
    glEnd();

    // Labeling vertices
    drawText(8, 4, "(8,4)");
    drawText(2, 4, "(2,4)");
    drawText(0, 8, "(0,8)");
    drawText(3, 12, "(3,12)");
    drawText(7, 12, "(7,12)");
    drawText(10, 8, "(10,8)");
}

// Function to check if a point is inside the polygon (Ray-casting algorithm)
int isInsidePolygon(float x, float y) {
    int vertices[6][2] = {{8, 4}, {2, 4}, {0, 8}, {3, 12}, {7, 12}, {10, 8}};
    int count = 0, i, j;
    for (i = 0, j = 5; i < 6; j = i++) {
        if ((vertices[i][1] > y) != (vertices[j][1] > y) &&
            (x < (vertices[j][0] - vertices[i][0]) * (y - vertices[i][1]) / 
            (vertices[j][1] - vertices[i][1]) + vertices[i][0])) {
            count++;
        }
    }
    return count % 2;  // If odd, point is inside
}

// Function to fill the polygon with evenly spaced asterisks
void fillPolygonWithAsterisks() {
    glColor3f(0.0, 1.0, 0.0);  // Green for asterisks

    // Iterate within the polygon's bounding box, avoiding edges
    for (float y = 5; y <= 11; y += 0.8) {  // Smaller step size for better fill
        for (float x = 1.5; x <= 9.5; x += 0.8) {
            // Ensure asterisks are inside and avoid the (10,8)-(7,12) edge
            if (isInsidePolygon(x, y) && !(x >= 7.5 && y >= 10.5)) {  
                glRasterPos2f(x, y);
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '*');
            }
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawPolygon();
    fillPolygonWithAsterisks();
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
    glutCreateWindow("Q4aiii: Polygon with Green Asterisks Fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
