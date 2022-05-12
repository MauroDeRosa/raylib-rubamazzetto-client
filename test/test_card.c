#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "game/card.h"


int main(int argc, char const *argv[])
{
    CardsInit();
    
    assert(cards[0].suit  == SUIT_DENARI  && cards[0].value == 1);
    assert(cards[10].suit == SUIT_SPADE   && cards[0].value == 1);
    assert(cards[20].suit == SUIT_BASTONI && cards[0].value == 1);
    assert(cards[30].suit == SUIT_COPPE   && cards[0].value == 1);

    return 0;
}
