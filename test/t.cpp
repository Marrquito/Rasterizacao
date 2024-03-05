#include <GL/glut.h>

#define IMAGE_WIDTH  512
#define IMAGE_HEIGHT 512

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int incx = (x2 > x1) ? 1 : -1;
    int incy = (y2 > y1) ? 1 : -1;

    int x = x1;
    int y = y1;

    drawPixel(x, y);

    if (dx > dy) {
        int p = 2 * dy - dx;

        for (int i = 0; i < dx; ++i) {
            x += incx;
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += incy;
                p += 2 * (dy - dx);
            }
            drawPixel(x, y);
        }
    } else {
        int p = 2 * dx - dy;

        for (int i = 0; i < dy; ++i) {
            y += incy;
            if (p < 0) {
                p += 2 * dx;
            } else {
                x += incx;
                p += 2 * (dx - dy);
            }
            drawPixel(x, y);
        }
    }
}

void drawTriangle() {
    int x1 = 100, y1 = 100;
    int x2 = 200, y2 = 300;
    int x3 = 300, y3 = 100;

    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1);

    int midX = IMAGE_WIDTH / 2;
    int midY = IMAGE_HEIGHT / 2;

    drawLine(midX, midY, 0, 0);
    drawLine(midX, midY, midX, 0);
    drawLine(midX, midY, IMAGE_WIDTH, 0);
    drawLine(midX, midY, IMAGE_WIDTH, midY);
    drawLine(midX, midY, IMAGE_WIDTH, IMAGE_HEIGHT);
    drawLine(midX, midY, midX, IMAGE_HEIGHT);
    drawLine(midX, midY, 0, IMAGE_HEIGHT);
    drawLine(midX, midY, 0, midY);

    drawTriangle();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, IMAGE_WIDTH, IMAGE_HEIGHT, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);

    glutCreateWindow("Casinha com OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
