#ifndef __SCENEMAINMENU_H__
#define __SCENEMAINMENU_H__

#include "SceneManager/Scene.h"

void SceneMainMenuStart();
void SceneMainMenuUpdate();
void SceneMainMenuFixedUpdate();
void SceneMainMenuRender();
void SceneMainMenuExit();

DefineScene(SceneMainMenu, "SceneMainMenu",  SceneMainMenuStart, SceneMainMenuUpdate, SceneMainMenuFixedUpdate, SceneMainMenuRender, SceneMainMenuExit);

#endif /* __SCENEMAINMENU_H__ */