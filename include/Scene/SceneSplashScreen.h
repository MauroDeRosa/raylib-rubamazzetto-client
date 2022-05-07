#ifndef __SCENESPLASHSCREEN_H__
#define __SCENESPLASHSCREEN_H__

#include "Scene.h"

void SceneSplashScreenStart();
void SceneSplashScreenUpdate();
void SceneSplashScreenFixedUpdate();
void SceneSplashScreenRender();
void SceneSplashScreenExit();

DefineScene(SceneSplashScreen, "SceneSplashScreen",  SceneSplashScreenStart, SceneSplashScreenUpdate, SceneSplashScreenFixedUpdate, SceneSplashScreenRender, SceneSplashScreenExit);

#endif /* __SCENESPLASHSCREEN_H__ */
