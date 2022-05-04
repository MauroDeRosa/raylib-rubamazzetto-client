#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <raylib.h>

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
    SceneCallback onRender;
    SceneCallback onExit;
    void *data;
} Scene;

#define DefineScene(name, nameString, onInit, onStart, onUpdate, onRender, onExit) static Scene name = (Scene) { nameString, onInit, onStart, onUpdate, onRender, onExit };

typedef struct
{
    bool running;
    Scene *current;
    Scene *next;
    SceneManagerState status;
}SceneManager_t;

static SceneManager_t SceneManager;

bool SceneManagerInit(Scene *startScene);
void SceneManagerLoop();
void SceneManagerSetState(SceneManagerState);
void SceneManagerSetNext(Scene *nextScene);

void _SceneManagerSceneInit();
void _SceneManagerNext();
void _SceneManagerClose();


#endif /* __SCENEMANAGER_H__ */
