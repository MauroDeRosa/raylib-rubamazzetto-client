#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

typedef enum
{
    SCENECBST_FALIURE,
    SCENECBST_SUCCESS,
    SCENECBST_SCENECHANGE,
    SCENECBST_SCMGRCLOSE
} SceneCallbackStatus;

typedef struct
{
    SceneCallbackStatus status;
    Scene *nextScene;
} SceneCallbackReturn;

#define SceneReturn(status, nextScenePtr) return (SceneCallbackReturn) {status, nextScenePtr};
#define SceneReturnFaliure() return (SceneCallbackReturn) {SCENECBST_FALIURE, 0};
#define SceneReturnChangeScene(nextScenePtr) return (SceneCallbackReturn) {SCENECBST_SCENECHANGE, nextScenePtr};
#define SceneReturnCloseScMgr() return (SceneCallbackReturn) {SCENECBST_SCMGRCLOSE, 0};

typedef SceneCallbackReturn (*SceneCallback)(int argc, ...);

typedef struct
{
    const char* name;
    SceneCallback onInit;
    SceneCallback onStart;
    SceneCallback onUpdate;
    SceneCallback onRender;
    SceneCallback onExit;
} Scene;

#define DefineScene(name, nameString, onInit, onStart, onUpdate, onRender, onExit) static Scene name = (Scene_t) { nameString, onInit, onStart, onUpdate, onRender, onExit };

Scene *_sceneManagerCurrent = NULL;
Scene *_sceneManagerQuit = NULL;

bool SceneManagerInit(Scene *startScene, Scene *quitScene);
void SceneManagerLoop(bool quitSignal);
void SceneManagerTransition(Scene *nextScene);
void SceneManagerClose();
void SceneManagerOnFaliure(Scene *scene);

#endif /* __SCENEMANAGER_H__ */
