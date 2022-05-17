#include "gui/ui_text.h"
#include "gui/ui_align.h"
#include <raymath.h>

#define UI_TEXT_SHADOW_OFFSET 3.0f
#define UI_TEXT_SHADOW_OPACITY 0.5f

void uiTextDraw(const char* text, Vector2 position, enum uiAlignmentHorizontal halign, enum uiAlignmentVertical valign, int fontSize, Color color, bool shadow)
{
    int textWidth = MeasureText(text, fontSize);

    position = uiGetAlignedPosition(position, (Vector2){textWidth, fontSize}, halign, valign);

    if(shadow)
    {
        Vector2 shadowPosition = Vector2Add( position, (Vector2){-UI_TEXT_SHADOW_OFFSET, UI_TEXT_SHADOW_OFFSET} );
        DrawText(text, shadowPosition.x, shadowPosition.y, fontSize, ColorAlpha(BLACK, Clamp(color.a/255.0f, 0.0f, UI_TEXT_SHADOW_OPACITY)) );
    }
    DrawText(text, position.x, position.y, fontSize, color);
}