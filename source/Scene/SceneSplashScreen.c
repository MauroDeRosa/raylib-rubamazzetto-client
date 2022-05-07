#include "Scene/SceneSplashScreen.h" 

struct SceneSplashScreenData
{
    // insert your scene variables here
    int example;
}; struct SceneSplashScreenData _SceneSplashScreenData;
void SceneSplashScreenStart()
{
    struct SceneSplashScreenData* $ = &_SceneSplashScreenData;
    
}

void SceneSplashScreenUpdate()
{
    struct SceneSplashScreenData* $ = &_SceneSplashScreenData;
    
}

void SceneSplashScreenFixedUpdate()
{
    struct SceneSplashScreenData* $ = &_SceneSplashScreenData;
    if(SceneManager.Time() >= 2.0f)
        SceneManager.Next("NewScene");
}

void SceneSplashScreenRender()
{
    struct SceneSplashScreenData* $ = &_SceneSplashScreenData;

    DrawText("diocane", 100, 100, 20, RED);    
}

void SceneSplashScreenExit()
{
    struct SceneSplashScreenData* $ = &_SceneSplashScreenData;
    
}
