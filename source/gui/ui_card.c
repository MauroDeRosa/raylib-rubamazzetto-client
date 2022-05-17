#include "gui/ui_card.h"
#include "ResourceManager/ResourceManager.h"
#include "utils/logger.h"

void uiCardDraw(Card card, Vector2 position, float rotation, float scale, bool centerOrigin, float alpha, bool back)
{
    Vector2 origin = (Vector2){.x = 0, .y = 0};
    if (centerOrigin)
    {
        origin = (Vector2){(CARD_WIDTH * scale) / 2.0f, (CARD_HEIGHT * scale) / 2.0f};
    }

    if (cardsTexture != NULL)
    {
        Rectangle textureRect = (Rectangle){.x = (card.value - 1) * CARD_WIDTH, .y = card.suit * CARD_HEIGHT, .width = CARD_WIDTH, .height = CARD_HEIGHT};
        if (back == true)
        {
            textureRect.x = (0) * CARD_WIDTH;
            textureRect.y = (5 - 1) * CARD_HEIGHT;
        }

        Rectangle scaledDrawRect =  (Rectangle){.x = position.x, .y = position.y, .width = CARD_WIDTH * scale, .height = CARD_HEIGHT * scale};
        Color textureColor = (Color){.r=WHITE.r, .g=WHITE.g, .b=WHITE.b, .a=alpha};
        DrawTexturePro(*cardsTexture, textureRect, scaledDrawRect, origin, rotation, textureColor);
    }
    else
    {
        Log(LOG_ERROR, LOG_COLOR_YELLOW "[card] " LOG_COLOR_RESET "Cardsheet can't be get from resource manager");
    }
}