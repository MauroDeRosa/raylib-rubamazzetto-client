#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "utils/logger.h"
#include "ResourceManager/ResourceManager.h"
#include "SceneManager/SceneManager.h"
#include "SceneManager/Scenes.h"
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
    SceneManager.Start("SceneSplashScreen");

    ResourceManager.Unload();
    ResourceManager.Destroy();

    CloseWindow();

    return 0;
}