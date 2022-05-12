#include "gui/ui_card.h"
#include "gui/gui.h"
#include "ResourceManager/ResourceManager.h"
#include "utils/logger.h"

void DrawCard(Card card, Vector2 position, float rotation, float scale, bool front, bool centerOrigin)
{
    // TODO: use resourcemanager
    Vector2 origin = (Vector2){.x=0, .y=0};
    if(centerOrigin)
        origin = (Vector2){(CARD_WIDTH*scale) / 2.0f, (CARD_HEIGHT*scale) / 2.0f};

    Texture2D *cardsheet = (Texture2D*) ResourceManager.Get(RESOURCE_TEXTURE2D, "cardsheet");
    if (cardsheet != NULL)
    {
        DrawTexturePro(*cardsheet,
        (Rectangle){.x=(card.value-1)*CARD_WIDTH, .y=card.suit*CARD_HEIGHT, .width=CARD_WIDTH, .height=CARD_HEIGHT},
        (Rectangle){.x=position.x, .y=position.y, .width=CARD_WIDTH*scale, .height=CARD_HEIGHT*scale},
        origin, rotation, WHITE);
    }
    else
    {
        Log(LOG_ERROR, LOG_COLOR_YELLOW "[card] " LOG_COLOR_RESET "Cardsheet can't be get from resource manager");
    }
}