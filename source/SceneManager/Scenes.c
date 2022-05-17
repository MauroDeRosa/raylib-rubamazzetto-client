#include "SceneManager/Scenes.h"
#include "SceneManager/SceneManager.h"

#include "SceneManager/Scenes/SceneSplashScreen.h"
#include "SceneManager/Scenes/SceneLoadingScreen.h"
#include "SceneManager/Scenes/SceneMainMenu.h"
#include "SceneManager/Scenes/ScenePlayMenu.h"
#include "SceneManager/Scenes/SceneProfileLogin.h"

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"
#undef RAYGUI_IMPLEMENTATION

void RegisterScenes()
{
    smRegister(SceneSplashScreen.name, &SceneSplashScreen);
    smRegister(SceneLoadingScreen.name, &SceneLoadingScreen);
    smRegister(SceneMainMenu.name, &SceneMainMenu);
    smRegister(ScenePlayMenu.name, &ScenePlayMenu);
    smRegister(SceneProfileLogin.name, &SceneProfileLogin);
}
