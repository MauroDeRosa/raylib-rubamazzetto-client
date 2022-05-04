#ifndef __SCENELOGO_H__
#define __SCENELOGO_H__

#include "SceneManager.h"

void SceneLogoOnInit(void** data);
void SceneLogoOnStart(void** data);
void SceneLogoOnUpdate(void** data);
void SceneLogoOnRender(void** data);
void SceneLogoOnExit(void** data);

DefineScene(SceneLogo, "SceneLogo", SceneLogoOnInit, SceneLogoOnStart, SceneLogoOnUpdate, SceneLogoOnRender, SceneLogoOnExit);

#endif /* __SCENELOGO_H__ */
