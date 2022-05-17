#include "gui/ui_textbox.h"
#include "gui/ui_align.h"

#include <stdlib.h>
#include "external/raygui.h"

struct uiTextbox_t *uiTextboxCreate(Vector2 position, Vector2 size, enum uiAlignmentHorizontal halign, enum uiAlignmentVertical valign, unsigned int textLength, void (*onEnter)(struct uiTextbox_t *))
{
    struct uiTextbox_t *textBox = (struct uiTextbox_t *)calloc(1, sizeof(struct uiTextbox_t));

    
    textBox->position = uiGetAlignedPosition(position, size, halign, valign);
    textBox->size = size;
    textBox->textLength = textLength;
    textBox->isSelected = false;
    textBox->isEnterPressed = false;
    textBox->isJustSwitched = false;
    textBox->text = calloc(textLength + 1, sizeof(char));
    textBox->next = NULL;
    textBox->onEnter = onEnter;

    return textBox;
}

void uiTextboxSetNext(struct uiTextbox_t *textBox, struct uiTextbox_t *next)
{
    textBox->next = next;
}

void uiTextboxUpdate(struct uiTextbox_t *textBox)
{
    if (textBox->isSelected == false)
        return;

    // isJustSwitched prevents that with multiple textbox update tab results pressed for all textboxes in that update frame
    if (textBox->isJustSwitched)
    {
        textBox->isJustSwitched = false;
    }
    else
    {
        if (IsKeyPressed(KEY_TAB) && textBox->next != NULL)
        {
            textBox->isEnterPressed = false;
            textBox->isSelected = false;
            textBox->next->isSelected = true;
            textBox->next->isJustSwitched = true;
        }
    }
    if (IsKeyPressed(KEY_DELETE))
    {
        textBox->text[0] = '\0';
    }
    else if (textBox->isEnterPressed && textBox->onEnter != NULL)
    {
        textBox->isSelected = false;
        textBox->onEnter(textBox);
    }
}

void uiTextboxRender(struct uiTextbox_t *textBox)
{
    Rectangle textBoxRect = (Rectangle){
        .x = textBox->position.x,
        .y = textBox->position.y,
        .width = textBox->size.x,
        .height = textBox->size.y,
    };
    DrawRectangleRec(textBoxRect, WHITE);
    if (GuiTextBox(textBoxRect, textBox->text, textBox->textLength, textBox->isSelected))
    {
        textBox->isEnterPressed = IsKeyPressed(KEY_ENTER) && textBox->isSelected;
        if (textBox->isEnterPressed == false)
        {
            textBox->isSelected = !textBox->isSelected;
        }
    }
}

void uiTextboxFree(struct uiTextbox_t *textBox)
{
    free(textBox->text);
    free(textBox);
}
