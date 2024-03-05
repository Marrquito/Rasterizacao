#include "definitions.h"
#include "mygl.h"

#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void MyGlDraw(void)
{
    //*************************************************************************
    // Chame aqui as funções do mygl.h
    //*************************************************************************

    Triangle tg1(Point(400, 150), Point(500, 300), Point(300, 300), Rgba(0, 250, 0, 255));
    tg1.Draw();

    Triangle tg2(Point(150, 300), Point(300, 300), Point(250, 400), Rgba(255, 0, 255, 255));
    tg2.Draw();
    
    Point center(IMAGE_WIDTH/2, IMAGE_HEIGHT/2);

    for (int i = 0; i <= IMAGE_WIDTH; i++)
        for (int j = 0; j <= IMAGE_HEIGHT; j++) 
            if ( !(i % (IMAGE_WIDTH / 4) ) && !(j % (IMAGE_HEIGHT / 4)) ) 
                DrawLine(center, Point(i, j), Rgba(rand() % 255, rand() % 255, rand() % 255, 255 ));

}

void PutPixel(GLint x, GLint y, Rgba color) 
{
    int position        =    4 * ((y * IMAGE_WIDTH) + x);

    FBptr[position]     = color.r;
    FBptr[position + 1] = color.g;
    FBptr[position + 2] = color.b;
    FBptr[position + 3] = color.a;

}

void DrawPixel(GLint x, GLint y, Rgba color)
{
    PutPixel(x, y, color);
}

void DrawLine(Point p1, Point p2, Rgba color)
{
    GLint dx    = abs(GLint(p2.x - p1.x));
    GLint dy    = abs(GLint(p2.y - p1.y));
    GLint incx  = (p2.x > p1.x) ? 1 : -1;
    GLint incy  = (p2.y > p1.y) ? 1 : -1;

    GLint x     = p1.x;
    GLint y     = p1.y;

    DrawPixel(x, y, color);

    if (dx > dy)
    {
        GLint p = 2 * dy - dx;

        for (int i = 0; i < dx; ++i)
        {
            x += incx;

            if (p < 0) p += 2 * dy;
            else
            {
                y += incy;
                p += 2 * (dy - dx);
            }
            
            DrawPixel(x, y, color);
        }
    } 
    else 
    {
        GLint p = 2 * dx - dy;

        for (int i = 0; i < dy; ++i)
        {
            y += incy;
        
            if (p < 0) p += 2 * dx;
            else
            {
                x += incx;
                p += 2 * (dx - dy);
            }
            
            DrawPixel(x, y, color);
        }
    }
}