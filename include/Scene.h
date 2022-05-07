#ifndef __SCENE_H__
#define __SCENE_H__

#include <stdlib.h>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "uthash/uthash.h"
#include <raylib.h>
#include "raylib-extra/raygui.h"
#include "logger.h"

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
