#ifndef __UI_TEXTBOX_ALIGNED_H__
#define __UI_TEXTBOX_ALIGNED_H__

#include <stdbool.h>
#include <raylib.h>
#include "gui/ui_align.h"


struct uiTextbox_t
{
    Vector2 position;
    Vector2 size;
    bool isSelected;
    bool isEnterPressed;
    bool isJustSwitched;
    unsigned int textLength;
    char *text;
    struct uiTextbox_t *next;
    void (*onEnter)(struct uiTextbox_t*);
};

struct uiTextbox_t *uiTextboxCreate(Vector2 position, Vector2 size, enum uiAlignmentHorizontal halign, enum uiAlignmentVertical valign, unsigned int textLength, void (*onEnter)(struct uiTextbox_t*));
void uiTextboxUpdate(struct uiTextbox_t* textBox);
void uiTextboxSetNext(struct uiTextbox_t* textBox, struct uiTextbox_t* next);
void uiTextboxRender(struct uiTextbox_t* textBox);
void uiTextboxFree(struct uiTextbox_t* textBox);

#endif /* __UI_TEXTBOX_ALIGNED_H__ */