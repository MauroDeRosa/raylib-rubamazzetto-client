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
} smData_t;

int smInit();
int smRegister(const char *name, struct Scene_t *scene);
int smStart(const char *firstSceneName);
double smTime();
int smNext(const char *name);

int smLoop();
int smEnd();

#endif /* __SCENEMANAGER_H__ */
