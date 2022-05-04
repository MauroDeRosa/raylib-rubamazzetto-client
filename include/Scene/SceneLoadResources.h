#ifndef __SCENELOADRESOURCES_H__
#define __SCENELOADRESOURCES_H__

#include "SceneManager.h"

void SceneLoadResourcesOnInit (void** _data);
void SceneLoadResourcesOnStart  (void** _data);
void SceneLoadResourcesOnUpdate (void** _data);
void SceneLoadResourcesOnRender (void** _data);
void SceneLoadResourcesOnExit (void** _data);

DefineScene(SceneLoadResources, "SceneLoadResources", SceneLoadResourcesOnInit, SceneLoadResourcesOnStart, SceneLoadResourcesOnUpdate, SceneLoadResourcesOnRender, SceneLoadResourcesOnExit);

#endif /* __SCENELOADRESOURCES_H__ */
