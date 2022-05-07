#include "SceneManager/Scenes.h"
#include "SceneManager/SceneManager.h"

#include "SceneManager/Scenes/SceneSplashScreen.h"
#include "SceneManager/Scenes/NewScene.h"

void RegisterScenes()
{
    SceneManager.Register(SceneSplashScreen.name, &SceneSplashScreen);
    SceneManager.Register(NewScene.name, &NewScene);
}
