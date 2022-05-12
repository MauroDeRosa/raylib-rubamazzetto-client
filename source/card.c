#include "card.h"

#include <string.h>
#include <stdio.h>
#include <ResourceManager/ResourceManager.h>

const char *CardSuitString[4] = {
    "Denari",
    "Spade",
    "Bastoni",
    "Coppe"};

Card cards[40];
Texture2D cardsheet;

void CardsInit()
{
    for (enum CardSuit i = SUIT_DENARI; i <= SUIT_COPPE; i++)
    {
        for (unsigned char j = 1; j <= 10; j++)
        {
            cards[(10*i)+(j-1)] = (Card){.suit=i, .value=j};
        }    
    }
    cardsheet = LoadTexture(CARD_TEXTURE_FILE);
}

void PrintCard(Card card, bool verbose)
{
    char cardString[11] = "";
    sprintf(cardString, "%s%s%u",
            verbose ? CardSuitString[card.suit] : CardSuitString[card.suit][0],
            verbose ? " " : "",
            card.value);
    printf("%s", cardString);
};

void DrawCard(Card card, Vector2 position, float rotation, float scale, bool front, bool centerOrigin)
{
    // TODO: use resourcemanager
    Vector2 origin = (Vector2){.x=0, .y=0};
    if(centerOrigin)
        origin = (Vector2){(CARD_WIDTH*scale) / 2.0f, (CARD_HEIGHT*scale) / 2.0f};

    DrawTexturePro(cardsheet,
    (Rectangle){.x=(card.value-1)*CARD_WIDTH, .y=card.suit*CARD_HEIGHT, .width=CARD_WIDTH, .height=CARD_HEIGHT},
    (Rectangle){.x=position.x, .y=position.y, .width=CARD_WIDTH*scale, .height=CARD_HEIGHT*scale},
    origin,
    rotation, WHITE);
}