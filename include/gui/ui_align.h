#ifndef __UI_ALIGN_H__
#define __UI_ALIGN_H__

#include <raylib.h>

enum uiAlignmentHorizontal{
    UI_HALIGN_LEFT,
    UI_HALIGN_CENTER,
    UI_HALIGN_RIGHT
};

enum uiAlignmentVertical{
    UI_VALIGN_TOP,
    UI_VALIGN_CENTER,
    UI_VALIGN_BOTTOM
};

Vector2 uiGetAlignedPosition(Vector2 position, Vector2 size, enum uiAlignmentHorizontal halign, enum uiAlignmentVertical valign);

#endif /* __UI_ALIGN_H__ */
