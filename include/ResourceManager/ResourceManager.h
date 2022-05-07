#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <raylib.h>
#include "external/uthash/uthash.h"
#include "Config.h"

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
extern const char *ResourceTypeString[];

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
} Resource_u;

/**
 * @brief The Resource Data Structure:
 */
struct Resource_t
{
    char name[100];     ///< Key value for the HashMap
    ResourceType type;  ///< The Resource Type
    char path[100];     ///< The Resource file path
    Resource_u data;  ///< The Resource data union
    UT_hash_handle hh;  ///< Hash handler for the uthash library
};

extern struct Resource_t *ResourceManagerMap;    ///< @brief The Resource HashMap pointer

/**
 * @brief The resource object structure
 */
typedef struct
{
    int (*Init)();  ///< @see ResourceManagerInit()
    int (*AddResource)(ResourceType type, const char *name, const char *path);  ///< @see ResourceManagerAddResource(ResourceType type, const char* name, const char* path)
    int (*RemoveResource)(ResourceType type, const char *name); ///< @see ResourceManagerRemoveResource(Resource type, const char* name)
    int (*Load)();  ///< @see ResourceManagerLoad()
    void *(*Get)(ResourceType type, const char *name);  ///< @see ResourceManagerGet(ResourceType type, const char* name)
    int (*Unload)();    ///< @see  ResourceManagerUnload()
    int (*Destroy)();   ///< @see ResourceManagerDestroy() 
} ResourceManager_t;

#pragma endregion private_resource_manager_data_types

#pragma region private_resource_manager_cls_and_methods

/**
 * @brief Get a string in the form "ResourceType_name"
 * 
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see Resource_t
 * @return char* a string containing "ResourceType_name" (must be freed) @see ResourceType @see Resource_t
 */
char *ResourceManagerGetResourceName(ResourceType type, const char *name);

/**
 * @brief 
 * 
 * @param fullName A string in the form "ResourceType_name" used as key value in the ResourceManagerMap HashMap
 * @return struct Resource_t* The pointer to the Resource element found in Hasmap. NULL if nothing was found @see Resource_t
 */
struct Resource_t *ResourceManagerGetResourcePointer(char *fullName);

/**
 * @brief 
 * 
 * @param resource 
 * @return void* 
 */
void *ResourceManagerGetResourceDataPointer(struct Resource_t *resource);

#pragma endregion private_resource_manager_cls_and_methods

#pragma region public_resource_manager_obj_and_methods

/**
 * @brief Initialize the ResourceManager HashMap @see ResourceManagerMap
 * 
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int ResourceManagerInit();

/**
 * @brief adds a resource of the specified name, type and path to the ResourceManagerMap HashMap
 * 
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see Resource_t
 * @param path the relative path to the Resource file, from the executable location
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int ResourceManagerAddResource(ResourceType type, const char *name, const char *path);

/**
 * @brief removes a resource of the specified name and type from the ResourceManagerMap HashMap
 * 
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see Resource_t
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int ResourceManagerRemoveResource(ResourceType type, const char *name);

/**
 * @brief iterates through Resource HashMap and call the exact Raylib Load function for each Resource Type
 * 
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int ResourceManagerLoad();

/**
 * @brief gets a pointer to the resource data of the specified ResourceType after being loaded through ResourceManagerLoad()
 * @param type the type of the Resource to get @see ResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see Resource_t
 * @return void* 
 */
void *ResourceManagerGet(ResourceType type, const char *name);

/**
 * @brief iterates through Resource HashMap and call the exact Raylib Unload function for each Resource Type
 * 
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int ResourceManagerUnload();

/**
 * @brief iterates through Resource HashMap, dereference HashMap elements and frees memory
 * 
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int ResourceManagerDestroy();

extern ResourceManager_t ResourceManager; ///< @brief ResourceManager global variable to access Resource Manager's callbacks

#pragma endregion public_resource_manager_obj_and_methods

#endif /* __RESOURCEMANAGER_H__ */
