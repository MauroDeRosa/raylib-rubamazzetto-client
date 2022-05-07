#ifndef __SCENE_H__
#define __SCENE_H__

#include "SceneManager/SceneManager.h"
#include "ResourceManager/ResourceManager.h"
#include "external/uthash/uthash.h"
#include "utils/logger.h"

#include <stdlib.h>
#include <raylib.h>
#include "external/raygui.h"

struct Scene_t
{
    const char *name;
    double startTime;

    void (*Start)();
    void (*Update)();
    void (*FixedUpdate)();
    void (*Render)();
    void (*Exit)();
    UT_hash_handle hh;
};

#define DefineScene(name, nameString, Start, Update, FixedUpdate, Render, Exit) \
static struct Scene_t name = { \
    nameString , \
    0.0 , \
    Start , \
    Update , \
    FixedUpdate , \
    Render , \
    Exit \
};


#endif /* __SCENE_H__ */
