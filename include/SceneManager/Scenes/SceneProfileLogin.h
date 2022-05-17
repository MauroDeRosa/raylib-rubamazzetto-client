#ifndef __SCENEPROFILELOGIN_H__
#define __SCENEPROFILELOGIN_H__

#include "SceneManager/Scene.h"

void SceneProfileLoginStart();
void SceneProfileLoginUpdate();
void SceneProfileLoginFixedUpdate();
void SceneProfileLoginRender();
void SceneProfileLoginExit();

DefineScene(SceneProfileLogin, "SceneProfileLogin",  SceneProfileLoginStart, SceneProfileLoginUpdate, SceneProfileLoginFixedUpdate, SceneProfileLoginRender, SceneProfileLoginExit);

#endif /* __SCENEPROFILELOGIN_H__ */
