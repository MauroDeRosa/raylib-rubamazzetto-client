#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raylib-extra/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "logger.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene/Scenes.h"
#include "Config.h"

#include <libgen.h>
#include <string.h>

int main(int argc, char** argv)
{
    SetTraceLogCallback(LogVaList);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    ResourceManager.Init();

    SceneManager.Init();
    RegisterScenes();
    SceneManager.Start("SplashScreen");

    ResourceManager.Unload();
    ResourceManager.Destroy();

    CloseWindow();

    return 0;
}