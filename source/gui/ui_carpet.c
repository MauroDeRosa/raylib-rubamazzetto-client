#include <raylib.h>
#include "external/raygui.h"

#include "config.h"
#include "gui/gui.h"
#include "gui/ui_carpet.h"

Texture2D uiCarpetNoise;

void uiCarpetInit()
{
    Image noiseImage = GenImageWhiteNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 0.4f);
    uiCarpetNoise = LoadTextureFromImage(noiseImage);
    UnloadImage(noiseImage);
}

void uiCarpetRender()
{
    ClearBackground(DARKGREEN);
    DrawTexture(uiCarpetNoise, 0, 0, (Color){0xFF,0xFF,0xFF, 0x22});
}

void uiCarpetUnload()
{
    UnloadTexture(uiCarpetNoise);
}