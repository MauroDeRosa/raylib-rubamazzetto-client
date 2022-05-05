#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <raylib.h>
#include "uthash/uthash.h"

#define RESOURCE_MANAGER_SUCCESS 0
#define RESOURCE_MANAGER_WARNING 1
#define RESOURCE_MANAGER_ERROR 2

/* -----------PUBLIC RESOURCE MANAGER RESOURCE TYPES----------- */
#pragma region resource_types_and_resource_type_strings

typedef enum
{
    RESOURCE_IMAGE,
    RESOURCE_TEXTURE,
    RESOURCE_TEXTURE2D,
    RESOURCE_TEXTURECUBEMAP,
    RESOURCE_RENDERTEXTURE,
    RESOURCE_RENDERTEXTURE2D,
    RESOURCE_NPATCHINFO,
    RESOURCE_GLYPHINFO,
    RESOURCE_FONT,
    RESOURCE_WAVE,
    RESOURCE_AUDIOSTREAM,
    RESOURCE_SOUND,
    RESOURCE_MUSIC
} ResourceType;

static const char *__ResourceTypeString[] = {
    "Image",
    "Texture",
    "Texture2D",
    "TextureCubemap",
    "RenderTexture",
    "RenderTexture2D",
    "NPatchInfo",
    "GlyphInfo",
    "Font",
    "Wave",
    "AudioStream",
    "Sound",
    "Music"};

#pragma endregion resource_types_and_resource_type_strings
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */

/* -----------PRIVATE RESOURCE MANAGER DATA TYPES-------------- */
#pragma region private_resource_manager_data_types

typedef union
{
    // 2D data structures (pixels, font...)
    Image Image;
    Texture Texture;
    Texture2D Texture2D;
    TextureCubemap TextureCubemap;
    RenderTexture RenderTexture;
    RenderTexture2D RenderTexture2D;
    NPatchInfo NPatchInfo;
    GlyphInfo GlyphInfo;
    Font Font;

    // Audio related data
    Wave Wave;
    AudioStream AudioStream;
    Sound Sound;
    Music Music;
} __Resource_u;

struct __Resource_t
{
    char name[100];
    ResourceType type;
    char path[100];
    __Resource_u resource;
    UT_hash_handle hh;
};

static struct __Resource_t *__ResourceManagerMap = NULL;

typedef struct
{
    int (*Init)();
    int (*AddResource)(ResourceType type, const char *name, const char *path);
    int (*RemoveResource)(ResourceType type, const char *name);
    int (*Load)();
    void *(*Get)(ResourceType type, const char *name);
    int (*Unload)();
    int (*Destroy)();

} __ResourceManager_t;

#pragma endregion private_resource_manager_data_types
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */


/* ---------PRIVATE RESOURCE MANAGER CLASS AND METHODS--------- */
#pragma region private_resource_manager_cls_and_methods

char *__ResourceManagerGetResourceName(ResourceType type, const char *name);
int __ResourceManagerExists(ResourceType type, const char *name);
void *__ResourceManagerGetResourcePointer(struct __Resource_t *resource);

#pragma endregion private_resource_manager_cls_and_methods
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */

/* ---------PUBLIC RESOURCE MANAGER OBJECT AND METHODS--------- */
#pragma region public_resource_manager_obj_and_methods

int __ResourceManagerInit();
int __ResourceManagerAddResource(ResourceType type, const char *name, const char *path);
int __ResourceManagerRemoveResource(ResourceType type, const char *name);
int __ResourceManagerLoad();
void *__ResourceManagerGet(ResourceType type, const char *name);
int __ResourceManagerUnload();
int __ResourceManagerDestroy();

static __ResourceManager_t ResourceManager = {
    __ResourceManagerInit,
    __ResourceManagerAddResource,
    __ResourceManagerRemoveResource,
    __ResourceManagerLoad,
    __ResourceManagerGet,
    __ResourceManagerUnload,
    __ResourceManagerDestroy};

#pragma endregion public_resource_manager_obj_and_methods
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */

#endif /* __RESOURCEMANAGER_H__ */
