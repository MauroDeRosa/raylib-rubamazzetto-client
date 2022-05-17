#include "gui/ui_align.h"

Vector2 uiGetAlignedPosition(Vector2 position, Vector2 size, enum uiAlignmentHorizontal halign, enum uiAlignmentVertical valign)
{
    Vector2 alignedPosition = position;

    if (halign == UI_HALIGN_CENTER)
    {
        alignedPosition.x -= size.x/2.0f;
    }
    else if (halign == UI_HALIGN_RIGHT)
    {
        alignedPosition.x -= size.x;
    }

    if (valign == UI_VALIGN_CENTER)
    {
        alignedPosition.y -= size.y/2.0f;
    }
    else if (valign == UI_VALIGN_BOTTOM)
    {
        alignedPosition.y -= size.y;
    }

    return alignedPosition;
}