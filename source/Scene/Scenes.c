#include "Scene/Scenes.h"
#include "SceneManager.h"

#include "Scene/SceneSplashScreen.h"

void RegisterScenes()
{
    SceneManager.Register(SplashScreen.name, &SplashScreen);
}
