#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

typedef struct RGBAColor {
    GLint r;
    GLint g;
    GLint b; 
    GLint a;

    RGBAColor(GLint _r, GLint _g, GLint _b, GLint _a) : r(_r), g(_g), b(_b), a(_a) {}
}Rgba;

struct Point {
    GLint x;
    GLint y;

    Point(GLint _x, GLint _y) : x(_x), y(_y) {}
};

//-----------------------------------------------------------------------------
void MyGlDraw(void);

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
void PutPixel(GLint x, GLint y, Rgba color);
void DrawLine(Point p1, Point p2, Rgba color);


typedef struct Triangle {
    Point v1;
    Point v2;
    Point v3;
    Rgba color;

    Triangle(Point _v1, Point _v2, Point _v3, Rgba _color) : v1(_v1), v2(_v2), v3(_v3), color(_color) {}
    
    void Draw()
    {
        DrawLine(v1, v2, color);
        DrawLine(v2, v3, color);
        DrawLine(v3, v1, color);
    }
}Tg;

#endif