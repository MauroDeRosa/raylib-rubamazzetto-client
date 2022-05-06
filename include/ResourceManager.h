#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <raylib.h>
#include "uthash/uthash.h"

#define RESOURCE_MANAGER_SUCCESS 0
#define RESOURCE_MANAGER_WARNING 1
#define RESOURCE_MANAGER_ERROR 2

/* -----------PUBLIC RESOURCE MANAGER RESOURCE TYPES----------- */
#pragma region resource_types_and_resource_type_strings

/**
 * @brief The resource Type: Image, Texture, Font, Wave, Sound, Music
 */
typedef enum
{
    RESOURCE_IMAGE,         ///< @see Image
    RESOURCE_TEXTURE2D,     ///< @see Texture2D
    RESOURCE_FONT,          ///< @see Font
    RESOURCE_WAVE,          ///< @see Wave
    RESOURCE_SOUND,         ///< @see Sound
    RESOURCE_MUSIC,         ///< @see Music
} ResourceType;


/**
 * @brief The string representation of the Resource Type
 */
static const char *__ResourceTypeString[] = {
    "Image",        ///< @see Image
    "Texture2D",    ///< @see Texture2D
    "Font",         ///< @see Font
    "Wave",         ///< @see Wave
    "Sound",        ///< @see Sound
    "Music"};       ///< @see Music

#pragma endregion resource_types_and_resource_type_strings
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */

/* -----------PRIVATE RESOURCE MANAGER DATA TYPES-------------- */
#pragma region private_resource_manager_data_types

/**
 * @brief The Resource data union (all the possible resource data types)
 */
typedef union
{
    Image Image;            ///< @see Image
    Texture2D Texture2D;    ///< @see Texture2D
    Font Font;              ///< @see Font
    Wave Wave;              ///< @see Wave
    Sound Sound;            ///< @see Sound
    Music Music;            ///< @see Music
} __Resource_u;

/**
 * @brief The Resource Data Structure:
 */
struct __Resource_t
{
    char name[100];     ///< Key value for the HashMap
    ResourceType type;  ///< The Resource Type
    char path[100];     ///< The Resource file path
    __Resource_u data;  ///< The Resource data union
    UT_hash_handle hh;  ///< Hash handler for the uthash library
};

static struct __Resource_t *__ResourceManagerMap = NULL;    ///< @brief The Resource HashMap pointer

/**
 * @brief The resource object structure
 */
typedef struct
{
    int (*Init)();  ///< @see __ResourceManagerInit()
    int (*AddResource)(ResourceType type, const char *name, const char *path);  ///< @see __ResourceManagerAddResource(ResourceType type, const char* name, const char* path)
    int (*RemoveResource)(ResourceType type, const char *name); ///< @see __ResourceManagerRemoveResource(Resource type, const char* name)
    int (*Load)();  ///< @see __ResourceManagerLoad()
    void *(*Get)(ResourceType type, const char *name);  ///< @see __ResourceManagerGet(ResourceType type, const char* name)
    int (*Unload)();    ///< @see  __ResourceManagerUnload()
    int (*Destroy)();   ///< @see __ResourceManagerDestroy() 
} __ResourceManager_t;

#pragma endregion private_resource_manager_data_types
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */


/* ---------PRIVATE RESOURCE MANAGER CLASS AND METHODS--------- */
#pragma region private_resource_manager_cls_and_methods

/**
 * @brief 
 * 
 * @param type 
 * @param name 
 * @return char* 
 */
char *__ResourceManagerGetResourceName(ResourceType type, const char *name);

/**
 * @brief 
 * 
 * @param fullName 
 * @return struct __Resource_t* 
 */
struct __Resource_t *__ResourceManagerGetResourcePointer(char *fullName);

/**
 * @brief 
 * 
 * @param resource 
 * @return void* 
 */
void *__ResourceManagerGetResourceDataPointer(struct __Resource_t *resource);

#pragma endregion private_resource_manager_cls_and_methods
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */

/* ---------PUBLIC RESOURCE MANAGER OBJECT AND METHODS--------- */
#pragma region public_resource_manager_obj_and_methods

/**
 * @brief 
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerInit();

/**
 * @brief 
 * 
 * @param type 
 * @param name 
 * @param path 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerAddResource(ResourceType type, const char *name, const char *path);

/**
 * @brief 
 * 
 * @param type 
 * @param name 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerRemoveResource(ResourceType type, const char *name);

/**
 * @brief 
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerLoad();

/**
 * @brief 
 * 
 * @param type 
 * @param name 
 * @return void* 
 */
void *__ResourceManagerGet(ResourceType type, const char *name);

/**
 * @brief 
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerUnload();

/**
 * @brief 
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerDestroy();

static __ResourceManager_t ResourceManager = {
    __ResourceManagerInit,
    __ResourceManagerAddResource,
    __ResourceManagerRemoveResource,
    __ResourceManagerLoad,
    __ResourceManagerGet,
    __ResourceManagerUnload,
    __ResourceManagerDestroy}; ///< @brief ResourceManager static global variable to access his public callbacks

#pragma endregion public_resource_manager_obj_and_methods
/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ */
/* //////////////////////////////////////////////////////////// */

#endif /* __RESOURCEMANAGER_H__ */
