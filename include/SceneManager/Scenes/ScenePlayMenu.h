#include "SceneManager/Scene.h"

void ScenePlayMenuStart();
void ScenePlayMenuUpdate();
void ScenePlayMenuFixedUpdate();
void ScenePlayMenuRender();
void ScenePlayMenuExit();

DefineScene(ScenePlayMenu, "ScenePlayMenu",  ScenePlayMenuStart, ScenePlayMenuUpdate, ScenePlayMenuFixedUpdate, ScenePlayMenuRender, ScenePlayMenuExit);