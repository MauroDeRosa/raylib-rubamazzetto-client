#ifndef __SCENELOADINGSCREEN_H__
#define __SCENELOADINGSCREEN_H__

#include "SceneManager/Scene.h"

void SceneLoadingScreenStart();
void SceneLoadingScreenUpdate();
void SceneLoadingScreenFixedUpdate();
void SceneLoadingScreenRender();
void SceneLoadingScreenExit();

DefineScene(SceneLoadingScreen, "SceneLoadingScreen",  SceneLoadingScreenStart, SceneLoadingScreenUpdate, SceneLoadingScreenFixedUpdate, SceneLoadingScreenRender, SceneLoadingScreenExit);

#endif /* __SCENELOADINGSCREEN_H__ */
