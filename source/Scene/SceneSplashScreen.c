#include "Scene/SceneSplashScreen.h"

SCENE_DATA_BEGIN

double lastFixedUpdate;
Texture2D *hisoka;

SCENE_DATA_END

void SplashScreenStart()
{
    ResourceManager.AddResource(RESOURCE_TEXTURE2D, "hisoka", "./resources/Texture/hisoka.png");
    ResourceManager.Load();
    $.lastFixedUpdate = 0;
    $.hisoka = ResourceManager.Get(RESOURCE_TEXTURE2D, "hisoka");
}

void SplashScreenUpdate()
{
    if(SceneManager.Time() > 5.0f)
        SceneManager.Next("END");
}

void SplashScreenFixedUpdate()
{
    $.lastFixedUpdate = SceneManager.Time();
}

void SplashScreenRender()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(*$.hisoka, 0, 0, WHITE);
    EndDrawing();
}

void SplashScreenExit()
{

}
