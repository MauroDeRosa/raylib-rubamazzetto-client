#ifndef __CARD_H__
#define __CARD_H__

#include <stdbool.h>
#include <raylib.h>

enum CardSuit {
    SUIT_DENARI,
    SUIT_SPADE,
    SUIT_BASTONI,
    SUIT_COPPE
};

extern const char *CardSuitString[4];


typedef struct
{
    enum CardSuit suit;
    unsigned char value;
}  Card;

extern Card cards[40];
extern Texture2D *cardsTexture;

void CardsInit();
void PrintCard(Card card, bool verbose);

#endif /* __CARD_H__ */
