#ifndef __SCENELOADSCREEN_H__
#define __SCENELOADSCREEN_H__

#include "SceneManager.h"

void SceneLoadScreenOnInit (void** _$);
void SceneLoadScreenOnStart  (void** _$);
void SceneLoadScreenOnUpdate (void** _$);
void SceneLoadScreenOnFixedUpdate (void** _$);
void SceneLoadScreenOnRender (void** _$);
void SceneLoadScreenOnExit (void** _$);

DefineScene(SceneLoadScreen, "SceneLoadScreen", SceneLoadScreenOnInit, SceneLoadScreenOnStart, SceneLoadScreenOnUpdate, SceneLoadScreenOnFixedUpdate, SceneLoadScreenOnRender, SceneLoadScreenOnExit);

#endif /* __SCENELOADSCREEN_H__ */
