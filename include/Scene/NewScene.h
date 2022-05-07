#ifndef __NEWSCENE_H__
#define __NEWSCENE_H__

#include "Scene.h"

void NewSceneStart();
void NewSceneUpdate();
void NewSceneFixedUpdate();
void NewSceneRender();
void NewSceneExit();

DefineScene(NewScene, "NewScene",  NewSceneStart, NewSceneUpdate, NewSceneFixedUpdate, NewSceneRender, NewSceneExit);

#endif /* __NEWSCENE_H__ */
