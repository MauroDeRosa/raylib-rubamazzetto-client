#include "Scene/Scenes.h"
#include "SceneManager.h"

#include "Scene/SceneSplashScreen.h"
#include "Scene/NewScene.h"

void RegisterScenes()
{
    SceneManager.Register(SceneSplashScreen.name, &SceneSplashScreen);
    SceneManager.Register(NewScene.name, &NewScene);
}
