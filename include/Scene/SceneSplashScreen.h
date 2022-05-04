#ifndef __SCENESPLASHSCREEN_H__
#define __SCENESPLASHSCREEN_H__

#include "SceneManager.h"

void SceneSplashScreenOnInit (void** _$);
void SceneSplashScreenOnStart  (void** _$);
void SceneSplashScreenOnUpdate (void** _$);
void SceneSplashScreenOnFixedUpdate (void** _$);
void SceneSplashScreenOnRender (void** _$);
void SceneSplashScreenOnExit (void** _$);

DefineScene(SceneSplashScreen, "SceneSplashScreen", SceneSplashScreenOnInit, SceneSplashScreenOnStart, SceneSplashScreenOnUpdate, SceneSplashScreenOnFixedUpdate, SceneSplashScreenOnRender, SceneSplashScreenOnExit);

#endif /* __SCENESPLASHSCREEN_H__ */
