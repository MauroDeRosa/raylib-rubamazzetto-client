#ifndef __UI_CARD_H__
#define __UI_CARD_H__

#include "game/card.h"

#define CARD_WIDTH  315
#define CARD_HEIGHT 505
#define CARD_TEXTURE_FILE "resources/texture/cardsheet.png"

void uiCardDraw(Card card, Vector2 position, float rotation, float scale, bool centerOrigin, float alpha, bool back);

#endif /* __UI_CARD_H__ */
