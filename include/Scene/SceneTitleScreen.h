#ifndef __SCENETITLESCREEN_H__
#define __SCENETITLESCREEN_H__

#include "SceneManager.h"

void SceneTitleScreenOnInit(void** data);
void SceneTitleScreenOnStart(void** data);
void SceneTitleScreenOnUpdate(void** data);
void SceneTitleScreenOnRender(void** data);
void SceneTitleScreenOnExit(void** data);

DefineScene(SceneTitleScreen, "SceneTitleScreen", SceneTitleScreenOnInit, SceneTitleScreenOnStart, SceneTitleScreenOnUpdate, SceneTitleScreenOnRender, SceneTitleScreenOnExit);

#endif /* __SCENETITLESCREEN_H__ */
