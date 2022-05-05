#include <raylib.h>
#include "logger.h"
#include "SceneManager.h"
#include "Scene/SceneSplashScreen.h"

#define RAYGUI_IMPLEMENTATION
#include "raylib-extra/raygui.h"
#undef RAYGUI_IMPLEMENTATION

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetTraceLogCallback(LogVaList);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    SetTargetFPS(60);

    SceneManagerInit(&SceneSplashScreen);
    SceneManagerLoop();

  
    CloseWindow();

    return 0;
}