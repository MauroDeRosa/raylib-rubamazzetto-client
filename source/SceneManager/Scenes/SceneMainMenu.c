#include "SceneManager/Scenes/SceneMainMenu.h"
#include <raylib.h>
#include <raymath.h>
#include "external/raygui.h"
#include "external/easings.h"
#include "utils/logger.h"
#include "gui/gui.h"
#include "ResourceManager/ResourceManager.h"

struct SceneMainMenuData
{
    Texture2D noise;

    float btnWidth;
    float btnHeight;
    float btnPosY;

    bool isBtnPlayPressed;
    bool isBtnLeaderboardPressed;
    bool isBtnProfilePressed;
};
struct SceneMainMenuData *_SceneMainMenuData;

void SceneMainMenuStart()
{
    struct SceneMainMenuData *$ = _SceneMainMenuData = calloc(1, sizeof(struct SceneMainMenuData));
    // memory and variables initialization here

    $->isBtnPlayPressed = false;
    $->isBtnLeaderboardPressed = false;
    $->isBtnProfilePressed = false;

    $->btnWidth = 200.0f;
    $->btnHeight = 100.0f;
    $->btnPosY = SCREEN_HEIGHT - ($->btnHeight * 1.5f) - 50.0f;
}

void SceneMainMenuUpdate()
{
    struct SceneMainMenuData *$ = _SceneMainMenuData;
    // update scene, called every frame

    if ($->isBtnPlayPressed)
    {
        smNext("ScenePlayMenu");
    }
    else if ($->isBtnProfilePressed)
    {
        smNext("SceneProfileLogin");
    }
    else if ($->isBtnLeaderboardPressed)
    {
        smNext("END");
    }
    
}

void SceneMainMenuFixedUpdate()
{
    struct SceneMainMenuData *$ = _SceneMainMenuData;
    // update scene, called every fixed timestep
}

void SceneMainMenuRender()
{
    struct SceneMainMenuData *$ = _SceneMainMenuData;
    // render scene, draw your art here <3
    uiCarpetRender();
    
    uiTextDraw("Ruba Mazzetto", (Vector2){ScreenCenter.x,  250}, UI_HALIGN_CENTER, UI_VALIGN_TOP, 100, ColorAlpha(RED, Clamp(smTime()/2, 0.0f, 1.0f)), true);

    $->isBtnProfilePressed = GuiButton((Rectangle){SCREEN_WIDTH * (1.0f / 4.0f) - $->btnWidth / 2, $->btnPosY, $->btnWidth, $->btnHeight}, "Profile");
    $->isBtnPlayPressed = GuiButton((Rectangle){SCREEN_WIDTH * (1.0f / 2.0f) - $->btnWidth / 2, $->btnPosY, $->btnWidth, $->btnHeight}, "Play");
    $->isBtnLeaderboardPressed = GuiButton((Rectangle){SCREEN_WIDTH * (3.0f / 4.0f) - $->btnWidth / 2, $->btnPosY, $->btnWidth, $->btnHeight}, "Leaderboard");
}

void SceneMainMenuExit()
{
    struct SceneMainMenuData *$ = _SceneMainMenuData;
    // TODO: clean memory here pls :3
    free(_SceneMainMenuData);
}
