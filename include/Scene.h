#ifndef __SCENE_H__
#define __SCENE_H__

#include <stdlib.h>
#include "SceneManager.h"
#include "uthash/uthash.h"

struct Scene_t
{
    const char *name;
    double setupTime;
    void *context;

    void (*Setup)();
    void (*Start)();
    void (*Update)();
    void (*FixedUpdate)();
    void (*Render)();
    void (*Exit)();
    UT_hash_handle hh;
};

#define DefineScene(name, nameString, dataPtr, Setup, Start, Update, FixedUpdate, Render, Exit) \
Scene_t name = { \
    nameString, \
    { nameString , 0, dataPtr } , \
    Setup , \
    Start , \
    Update , \
    FixedUpdate , \
    Render , \
    Exit \
};

// TODO: define context operator
//#define $(var) 

#endif /* __SCENE_H__ */
