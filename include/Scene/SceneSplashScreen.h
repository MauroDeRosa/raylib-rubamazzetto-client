#ifndef __SCENESPLASHSCREEN_H__
#define __SCENESPLASHSCREEN_H__

#include "SceneManager.h"

void SceneSplashScreenOnInit(void **_data);
void SceneSplashScreenOnStart(void **_data);
void SceneSplashScreenOnUpdate(void **_data);
void SceneSplashScreenOnRender(void **_data);
void SceneSplashScreenOnExit(void **_data);

DefineScene(SceneSplashScreen, "SceneSplashScreen", SceneSplashScreenOnInit, SceneSplashScreenOnStart, SceneSplashScreenOnUpdate, SceneSplashScreenOnRender, SceneSplashScreenOnExit);

#endif /* __SCENESPLASHSCREEN_H__ */
