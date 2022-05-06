#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raylib-extra/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "logger.h"
#include "ResourceManager.h"
#include "Scene/Scenes.h"
#include "Config.h"



int main(void)
{
    SetTraceLogCallback(LogVaList);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    ResourceManager.Init();
    RegisterScenes();
    

    ResourceManager.Unload();
    ResourceManager.Destroy();
    
    // SceneManagerInit(&SceneSplashScreen);
    // SceneManagerLoop();

  
    CloseWindow();

    return 0;
}