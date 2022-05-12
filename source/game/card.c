#include "game/card.h"

#include <string.h>
#include <stdio.h>
#include <ResourceManager/ResourceManager.h>

const char *CardSuitString[4] = {
    "Denari",
    "Spade",
    "Bastoni",
    "Coppe"};

Card cards[40];

void CardsInit()
{
    for (enum CardSuit i = SUIT_DENARI; i <= SUIT_COPPE; i++)
    {
        for (unsigned char j = 1; j <= 10; j++)
        {
            cards[(10*i)+(j-1)] = (Card){.suit=i, .value=j};
        }    
    }
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
