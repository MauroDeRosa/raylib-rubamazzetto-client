#include "Scene/SceneTitleScreen.h"

void SceneTitleScreenOnInit(void** data)
{
}

void SceneTitleScreenOnStart(void** data)
{

}

void SceneTitleScreenOnUpdate(void** data)
{
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        SceneManagerSetState(SCENEMGR_CLOSE);
    }
}

void SceneTitleScreenOnRender(void** data)
{
    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, 800, 450, GREEN);
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
}

void SceneTitleScreenOnExit(void** data)
{
}