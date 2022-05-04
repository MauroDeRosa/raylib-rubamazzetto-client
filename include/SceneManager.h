#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <stdbool.h>

#define SCENE_MANAGER_FIXEDUPDATE_STEP 0.25f

typedef enum
{
    SCENEMGR_FALIURE,
    SCENEMGR_SUCCESS,
    SCENEMGR_NEXT,
    SCENEMGR_CLOSE
} SceneManagerState;

typedef void (*SceneCallback)(void** data);

typedef struct
{
    const char* name;
    SceneCallback onInit;
    SceneCallback onStart;
    SceneCallback onUpdate;
    SceneCallback onFixedUpdate;
    SceneCallback onRender;
    SceneCallback onExit;
    void *data;
} Scene;

#define DefineScene(name, nameString, onInit, onStart, onUpdate, onFixedUpdate, onRender, onExit) static Scene name = (Scene) { nameString, onInit, onStart, onUpdate, onFixedUpdate, onRender, onExit };

typedef struct
{
    bool running;
    Scene *current;
    Scene *next;
    SceneManagerState status;
    float fixedUpdateTimer;
    double sceneInitTime;
}SceneManager_t;

static SceneManager_t SceneManager;

bool SceneManagerInit(Scene *startScene);
void SceneManagerLoop();
void SceneManagerSetState(SceneManagerState);
void SceneManagerSetNext(Scene *nextScene);
double SceneManagerGetTime();

void _SceneManagerSceneInit();
void _SceneManagerNext();
void _SceneManagerClose();


#endif /* __SCENEMANAGER_H__ */
