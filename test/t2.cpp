#include <GL/glut.h>

// Simulação de um buffer de acesso direto à memória
unsigned char* FBptr; 
#define IMAGE_WIDTH  512
#define IMAGE_HEIGHT 512

void PutPixel(int x, int y, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    int position = ((y * IMAGE_WIDTH) + x) * 4;

    FBptr[position] = red;
    FBptr[position + 1] = green;
    FBptr[position + 2] = blue;
    FBptr[position + 3] = alpha;
}

void drawPixel(int x, int y) {
    PutPixel(x, y, 255, 255, 255, 255);
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
    glPointSize(1.0);

    drawTriangle();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, IMAGE_WIDTH, 0, IMAGE_HEIGHT);
}

int main(int argc, char** argv) {
    FBptr = new unsigned char[IMAGE_WIDTH * IMAGE_HEIGHT * 4];

    for (unsigned int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i++) {
        FBptr[i * 4] = 0;
        FBptr[i * 4 + 1] = 0;
        FBptr[i * 4 + 2] = 0;
        FBptr[i * 4 + 3] = 255;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    glutCreateWindow("Triângulo com Bresenham");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    delete[] FBptr;

    return 0;
}
