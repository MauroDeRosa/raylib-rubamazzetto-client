#ifndef __CARD_H__
#define __CARD_H__

#include <stdbool.h>
#include <raylib.h>

#define CARD_WIDTH  315
#define CARD_HEIGHT 505
#define CARD_TEXTURE_FILE "resources/texture/cardsheet.png"

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

void CardsInit();
void PrintCard(Card card, bool verbose);
void DrawCard(Card card, Vector2 position, float rotation, float scale, bool front, bool centerOrigin);

#endif /* __CARD_H__ */
