#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <stdbool.h>
#include <stdlib.h>

#include "Config.h"
#include "Scene.h"

typedef struct
{
    struct Scene_t *currentScene;
    struct Scene_t *nextScene;
    bool isSceneEnded;
} SceneManagerAttribute_t;

typedef struct
{
    SceneManagerAttribute_t attr;
    int (*Init)();
    int (*Register)(const char *name, struct Scene_t *scene);
    int (*Start)();
    double (*Time)();
    int (*Next)(const char *name);
} SceneManager_t;

struct Scene_t *SceneManagerSceneMap;

int SceneManagerInit();
int SceneManagerRegister(const char *name, struct Scene_t *scene);
int SceneManagerStart(const char *firstSceneName);
double SceneManagerTime();
int SceneManagerNext(const char *name);

int SceneManagerLoop();
int SceneManagerEnd();

SceneManager_t SceneManager = {
    (SceneManagerAttribute_t){ NULL, NULL, false },
    SceneManagerInit,
    SceneManagerRegister,
    SceneManagerStart,
    SceneManagerTime,
    SceneManagerNext};

#endif /* __SCENEMANAGER_H__ */
