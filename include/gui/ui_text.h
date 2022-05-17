#ifndef __UI_TEXT_ALIGNED_H__
#define __UI_TEXT_ALIGNED_H__

#include <raylib.h>
#include <stdbool.h>

#include "gui/ui_align.h"

void uiTextDraw(const char* text, Vector2 position, enum uiAlignmentHorizontal halign, enum uiAlignmentVertical valign, int fontSize, Color color, bool shadow);

#endif /* __UI_TEXT_ALIGNED_H__ */
