#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <stdbool.h>
#include <stdlib.h>

#include "Config.h"
#include "SceneManager/Scene.h"

typedef struct
{
    struct Scene_t *map;
    struct Scene_t *currentScene;
    struct Scene_t *nextScene;
    bool isSceneEnded;
    float fixedStepTimer;
} SceneManagerAttribute_t;

typedef struct
{
    SceneManagerAttribute_t attr;
    int (*Init)();
    int (*Register)(const char *name, struct Scene_t *scene);
    int (*Start)(const char *firstSceneName);
    double (*Time)();
    int (*Next)(const char *name);
} SceneManager_t;

int SceneManagerInit();
int SceneManagerRegister(const char *name, struct Scene_t *scene);
int SceneManagerStart(const char *firstSceneName);
double SceneManagerTime();
int SceneManagerNext(const char *name);

int SceneManagerLoop();
int SceneManagerEnd();

static SceneManager_t SceneManager = {
    (SceneManagerAttribute_t){ NULL, NULL, NULL, false, 0},
    SceneManagerInit,
    SceneManagerRegister,
    SceneManagerStart,
    SceneManagerTime,
    SceneManagerNext};

#endif /* __SCENEMANAGER_H__ */
