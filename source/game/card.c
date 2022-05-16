#include "game/card.h"

#include <string.h>
#include <stdio.h>
#include <ResourceManager/ResourceManager.h>

const char *CardSuitString[4] = {
    "Denari",
    "Spade",
    "Bastoni",
    "Coppe"};

const char *CardSuitStringShort[4] = {
    "D",
    "S",
    "B",
    "C"};

Card cards[40];

Texture2D *cardsTexture;

void CardsInit()
{
    for (enum CardSuit i = SUIT_DENARI; i <= SUIT_COPPE; i++)
    {
        for (unsigned char j = 1; j <= 10; j++)
        {
            cards[(10*i)+(j-1)] = (Card){.suit=i, .value=j};
        }    
    }
    cardsTexture = rmGet(RM_TEXTURE2D, "cardsheet");
}

void PrintCard(Card card, bool verbose)
{
    char cardString[11] = "";
    sprintf(cardString, "%s%s%u",
            verbose ? CardSuitString[card.suit] : CardSuitStringShort[card.suit],
            verbose ? " " : "",
            card.value);
    printf("%s", cardString);
};
