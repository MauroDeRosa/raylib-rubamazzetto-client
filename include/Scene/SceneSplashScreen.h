#ifndef __SCENESPLASHSCREEN_H__
#define __SCENESPLASHSCREEN_H__

#include "Scene.h"

void SplashScreenStart();
void SplashScreenUpdate();
void SplashScreenFixedUpdate();
void SplashScreenRender();
void SplashScreenExit();

DefineScene(SplashScreen, "SplashScreen",  SplashScreenStart, SplashScreenUpdate, SplashScreenFixedUpdate, SplashScreenRender, SplashScreenExit);

#endif /* __SCENESPLASHSCREEN_H__ */
