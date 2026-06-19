#include "wrapper.hpp"

#include "geometry.hpp"

extern "C"
{
    EXPORT Line *CreateLine(Point start, Point end)
    {
        return new Line(start, end);
    }

    EXPORT void SetStartLine(Line *line, Point start)
    {
        line->SetStart(start);
    }

    EXPORT void SetEndLine(Line *line, Point end)
    {
        line->SetStart(end);
    }

    EXPORT void SetColorLine(Line *line, Color color)
    {
        line->SetColor(color);
    }

    EXPORT void RenderLine(Line *line)
    {
        line->Render();
    }

    EXPORT void DeleteLine(Line *line)
    {
        delete line;
    }
}