#ifndef GEOMETRY
#define GEOMETRY

#include "type.hpp"

class Line final
{
private:
    Point *_start, *_end;
    Color *_color;

public:
    Line(Point start, Point end, Color color = COLOR_WHITE); // TODO: line stroke

    /* Point methods */

    void SetStart(Point start);
    void SetEnd(Point start);

    // Point GetStart(void);
    // Point GetEnd(void);

    /* Color methods */

    void SetColor(Color color);

    /* Render methods */

    void Render(void);

    ~Line();
};

class Rectangle final
{
private:
    Rect *_rect;
    Color *_color;

public:
    Rectangle(Rect rect, Color color = COLOR_WHITE);

    /* Size methods */

    void SetW(UINT16 w);
    void SetH(UINT16 h);
    void SetSize(UINT16 w, UINT16 h);

    UINT16 GetW(void);
    UINT16 GetH(void);

    /* Position methods */

    void SetX(INT16 x);
    void SetY(INT16 y);
    void SetPosition(INT16 x, INT16 y);

    INT16 GetX(void);
    INT16 GetY(void);

    /* Color methods */

    void SetColor(Color color);

    /* Render methods */

    void Render(void);
    void RenderFill(void);

    ~Rectangle();
};

#endif // GEOMETRY