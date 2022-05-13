#include "SceneManager/Scenes/SceneSplashScreen.h"
#include <raylib.h>
#include <raymath.h>
#include "external/raygui.h"
#include "external/easings.h"
#include "gui/gui.h"

struct SceneSplashScreenData
{
    // insert your scene variables here
    int example;
};
struct SceneSplashScreenData *_SceneSplashScreenData;

void SceneSplashScreenStart()
{
    struct SceneSplashScreenData *$ = _SceneSplashScreenData = calloc(1, sizeof(struct SceneSplashScreenData));
    // memory and variables initialization here
}

void SceneSplashScreenUpdate()
{
    struct SceneSplashScreenData *$ = _SceneSplashScreenData;
    // update scene, called every frame
}

void SceneSplashScreenFixedUpdate()
{
    struct SceneSplashScreenData *$ = _SceneSplashScreenData;
    // update scene, called every fixed timestep
}

void SceneSplashScreenRender()
{
    struct SceneSplashScreenData *$ = _SceneSplashScreenData;

    ClearBackground(WHITE);
    float alpha = Clamp((SceneManager.Time() / 1.5f) * 0xFF, 0x00, 0xFF);
    Color raylibColor = (Color){0x00, 0x00, 0xBB, alpha};
    Color innerColor = (Color){0xEF, 0xEF, 0xEF, alpha};
    Color madeWithColor = (Color){0x00, 0x00, 0xEE, alpha};

    DrawRectangle(SCREEN_WIDTH / 2 - 128, SCREEN_HEIGHT / 2 - 128, 256, 256, raylibColor);
    DrawRectangle(SCREEN_WIDTH / 2 - 112, SCREEN_HEIGHT / 2 - 112, 224, 224, innerColor);
    DrawText("raylib", SCREEN_WIDTH / 2 - 44, SCREEN_HEIGHT / 2 + 48, 50, raylibColor);
    DrawText("Made by Mauro De Rosa", SCREEN_WIDTH / 2 - 110 + 5, SCREEN_HEIGHT / 2 + 5 - 112, 15, madeWithColor);
    DrawText("Powered by: ", SCREEN_WIDTH / 2 - 110 + 5, SCREEN_HEIGHT / 2 + 20 - 112, 10, madeWithColor);

    if (SceneManager.Time() > 1.5f)
    {
        float alpha = Clamp( ( (SceneManager.Time() - 4.0f) / 1.0f) * 0xFF, 0x00, 0xFF);
        Color fadeColor = (Color){.r = 0x00, .g = 0x00, .b = 0x00, .a = alpha};
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, fadeColor);
        
    }
}

void SceneSplashScreenExit()
{
    struct SceneSplashScreenData *$ = _SceneSplashScreenData;
    // TODO: clean memory here pls :3
    free(_SceneSplashScreenData);
}
