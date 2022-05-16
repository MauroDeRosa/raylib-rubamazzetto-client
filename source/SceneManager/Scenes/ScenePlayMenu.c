#include "SceneManager/Scenes/ScenePlayMenu.h"
#include <raylib.h>
#include <raymath.h>
#include "external/raygui.h"
#include "external/easings.h"
#include "utils/logger.h"
#include "gui/gui.h"
#include "game/User.h"

struct ScenePlayMenuData
{
    // insert your scene variables here
    struct uiLoginBox_t *loginBox[4];
    bool canPlay;
    bool isPlayPressed;
    bool isBackPressed;
};
struct ScenePlayMenuData *_ScenePlayMenuData;

void ScenePlayMenuStart()
{
    struct ScenePlayMenuData *$ = _ScenePlayMenuData = calloc(1, sizeof(struct ScenePlayMenuData));
    // memory and variables initialization here

    UsersLoad("users.dat");

    Vector2 pos = (Vector2){10.0f, 200.0f};
    for (size_t i = 0; i < 4; i++)
    {
        $->loginBox[i] = UiLoginBoxCreate(pos);
        pos.x += $->loginBox[i]->size.x + 20.0f;
    }
}

void ScenePlayMenuUpdate()
{
    struct ScenePlayMenuData *$ = _ScenePlayMenuData;
    // update scene, called every frame

    int loggedInCount = 0;
    for (size_t i = 0; i < 4; i++)
    {
        uiUpdateLoginBox($->loginBox[i]);
        if ($->loginBox[i]->isLoggedIn)
            loggedInCount++;
    }
    if (loggedInCount >= 2)
    {
        $->canPlay = true;
    }
    if ($->isPlayPressed)
    {
        smNext("END");
    }
    else if ($->isBackPressed)
    {
        smNext("SceneMainMenu");
    }
}

void ScenePlayMenuFixedUpdate()
{
    struct ScenePlayMenuData *$ = _ScenePlayMenuData;
    // update scene, called every fixed timestep
}

void ScenePlayMenuRender()
{
    struct ScenePlayMenuData *$ = _ScenePlayMenuData;
    // render scene, draw your art here <3

    uiCarpetRender();

    DrawText("SELECT YOUR PLAYERS", SCREEN_WIDTH / 2 - MeasureText("SELECT YOUR PLAYERS", 80) / 2, 20, 80, RED);
    for (size_t i = 0; i < 4; i++)
    {
        DrawText(
            TextFormat("Player %zu", i + 1),
            13.0f + i * ($->loginBox[i]->size.x + 20.0f),
            160, 30, ORANGE);
        uiRenderLoginBox($->loginBox[i]);
    }

    Vector2 pos = (Vector2){0.0f, 0.0f};

    $->isBackPressed = GuiButton((Rectangle){SCREEN_WIDTH - 210, SCREEN_HEIGHT - 110, 200, 100}, "Back");

    if ($->canPlay)
    {
        $->isPlayPressed = ((Rectangle){SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 110, 200, 100}, "Play");
    }
}

void ScenePlayMenuExit()
{
    struct ScenePlayMenuData *$ = _ScenePlayMenuData;
    // TODO: clean memory here pls :3
    for (size_t i = 0; i < 4; i++)
    {
        UiLoginBoxFree($->loginBox[i]);
    }
    free(_ScenePlayMenuData);
}
