#include "wrapper.hpp"

#include "geometry.hpp"

extern "C"
{
    EXPORT Rectangle *CreateRectangle(Rect rect)
    {
        return new Rectangle(rect);
    }

    void SetWRectangle(Rectangle *rect, UINT16 w)
    {
        rect->SetW(w);
    }

    void SetHRectangle(Rectangle *rect, UINT16 h)
    {
        rect->SetH(h);
    }

    UINT16 GetWRectangle(Rectangle *rect)
    {
        return rect->GetW();
    }

    UINT16 GetHRectangle(Rectangle *rect)
    {
        return rect->GetH();
    }

    void SetXRectangle(Rectangle *rect, INT16 x)
    {
        rect->SetX(x);
    }

    void SetYRectangle(Rectangle *rect, INT16 y)
    {
        rect->SetY(y);
    }

    INT16 GetXRectangle(Rectangle *rect)
    {
        return rect->GetX();
    }

    INT16 GetYRectangle(Rectangle *rect)
    {
        return rect->GetY();
    }

    void SetColorRectangle(Rectangle *rect, Color color)
    {
        rect->SetColor(color);
    }

    void RenderRectangle(Rectangle *rect)
    {
        rect->Render();
    }

    void RenderFillRectangle(Rectangle *rect)
    {
        rect->RenderFill();
    }

    EXPORT void DeleteRectangle(Rectangle *rect)
    {
        delete rect;
    }
}