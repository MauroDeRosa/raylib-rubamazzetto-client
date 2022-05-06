#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <raylib.h>
#include "uthash/uthash.h"

#define RESOURCE_MANAGER_SUCCESS 0
#define RESOURCE_MANAGER_WARNING 1
#define RESOURCE_MANAGER_ERROR 2

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

#pragma region private_resource_manager_cls_and_methods

/**
 * @brief Get a string in the form "ResourceType_name"
 * 
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see __Resource_t
 * @return char* a string containing "ResourceType_name" (must be freed) @see ResourceType @see __Resource_t
 */
char *__ResourceManagerGetResourceName(ResourceType type, const char *name);

/**
 * @brief 
 * 
 * @param fullName A string in the form "ResourceType_name" used as key value in the __ResourceManagerMap HashMap
 * @return struct __Resource_t* The pointer to the Resource element found in Hasmap. NULL if nothing was found @see __Resource_t
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

#pragma region public_resource_manager_obj_and_methods

/**
 * @brief Initialize the ResourceManager HashMap @see __ResourceManagerMap
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerInit();

/**
 * @brief adds a resource of the specified name, type and path to the __ResourceManagerMap HashMap
 * 
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see __Resource_t
 * @param path the relative path to the Resource file, from the executable location
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerAddResource(ResourceType type, const char *name, const char *path);

/**
 * @brief removes a resource of the specified name and type from the __ResourceManagerMap HashMap
 * 
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see __Resource_t
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerRemoveResource(ResourceType type, const char *name);

/**
 * @brief iterates through Resource HashMap and call the exact Raylib Load function for each Resource Type
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerLoad();

/**
 * @brief gets a pointer to the resource data of the specified ResourceType after being loaded through __ResourceManagerLoad()
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see __Resource_t
 * @return void* 
 */
void *__ResourceManagerGet(ResourceType type, const char *name);

/**
 * @brief iterates through Resource HashMap and call the exact Raylib Unload function for each Resource Type
 * 
 * @return int RESOURCE_MANAGER_ERROR or RESOURCE_MANAGER_WARNING or RESOURCE_MANAGER_SUCCESS
 */
int __ResourceManagerUnload();

/**
 * @brief iterates through Resource HashMap, dereference HashMap elements and frees memory
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

#endif /* __RESOURCEMANAGER_H__ */
