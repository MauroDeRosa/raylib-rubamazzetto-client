#include "SceneManager/Scenes/SceneLoadingScreen.h"
#include <raylib.h>
#include <raymath.h>
#include "external/raygui.h"
#include "external/easings.h"
#include "gui/gui.h"
#include "utils/logger.h"
struct SceneLoadingScreenData
{
    // insert your scene variables here
    enum
    {
        STATE_WAITING,
        STATE_LOADING
    } state;

    float progress;
    double elapsed;
};
struct SceneLoadingScreenData *_SceneLoadingScreenData;

void SceneLoadingScreenStart()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData = calloc(1, sizeof(struct SceneLoadingScreenData));
    // memory and variables initialization here
    $->state = STATE_WAITING;
    $->elapsed = 0;
    $->progress = 0;
}

void SceneLoadingScreenUpdate()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // update scene, called every frame
    switch ($->state)
    {
    case STATE_WAITING:
    {
        rmLoad();
        $->state = STATE_LOADING;
    }
    break;
    case STATE_LOADING:
    {
        $->elapsed += GetFrameTime();
        if (rmGetIsLoaded() && $->progress == 1.0f)
        {
            smNext("SceneMainMenu");
        }
    }
    break;
    }
}

void SceneLoadingScreenFixedUpdate()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // update scene, called every fixed timestep
}

void SceneLoadingScreenRender()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // render scene, draw your art here <3

    switch ($->state)
    {
    case STATE_WAITING:
        DrawText("PRESS ENTER to START LOADING DATA", 150, 170, 20, DARKGRAY);
        break;
    case STATE_LOADING:
    {
        float timePercentage = 0;
        $->progress = Clamp( (rmGetProgress() + $->elapsed/3.0f) / 2.0f, 0.0f, 1.0f);
        GuiProgressBar(
            (Rectangle){.x = 30, .y = SCREEN_HEIGHT / 2.0f + 20.0f, .width = SCREEN_WIDTH - 60, .height = 40},
            NULL, NULL,
            $->progress, 0, 1);
        DrawText("LOADING...", SCREEN_WIDTH / 2.0f - MeasureText("Loading...", 40) / 2.0f, SCREEN_HEIGHT / 2 - 20, 40, (int)(smTime()/1.0f)% 2 == 0 ? GRAY : LIGHTGRAY);
        break;
    }
    }
}

void SceneLoadingScreenExit()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // TODO: clean memory here pls :3
    CardsInit();
    free(_SceneLoadingScreenData);
}
