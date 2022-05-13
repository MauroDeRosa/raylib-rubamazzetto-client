#include "SceneManager/Scenes.h"
#include "SceneManager/SceneManager.h"

#include "SceneManager/Scenes/SceneSplashScreen.h"
#include "SceneManager/Scenes/SceneLoadingScreen.h"

void RegisterScenes()
{
    smRegister(SceneSplashScreen.name, &SceneSplashScreen);
    smRegister(SceneLoadingScreen.name, &SceneLoadingScreen);
}
