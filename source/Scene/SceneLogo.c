#include "Scene/SceneLogo.h"
#include "Scene/SceneTitleScreen.h"
#include <raylib.h>
#include <stdlib.h>

typedef struct
{
    int framesCounter;
} SceneLogoData;

void SceneLogoOnInit(void** data)
{
    *data = malloc(sizeof(SceneLogoData));
    if (*data == NULL)
        SceneManagerSetState(SCENEMGR_FALIURE);
    SceneManagerSetState(SCENEMGR_SUCCESS);
}

void SceneLogoOnStart(void** data)
{
    SceneLogoData *_data = *data;
    _data->framesCounter = 0;
}

void SceneLogoOnUpdate(void** data)
{
    SceneLogoData *_data = *data;

    // Update LOGO screen variables here!
    _data->framesCounter++;

    // Wait for 2 seconds (120 frames) before jumping to TITLE screen
    if (_data->framesCounter > 120)
    {
        SceneManagerSetNext(&SceneTitleScreen);
    }
}

void SceneLogoOnRender(void** data)
{
    ClearBackground(RAYWHITE);
    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
}

void SceneLogoOnExit(void** data)
{
    free(*data);
}