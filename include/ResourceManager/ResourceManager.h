#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <raylib.h>
#include "external/uthash/uthash.h"
#include "Config.h"

/**
 * @brief The resource Type: Image, Texture, Font, Wave, Sound, Music
 */
typedef enum
{
    RM_IMAGE,     ///< @see Image
    RM_TEXTURE2D, ///< @see Texture2D
    RM_FONT,      ///< @see Font
    RM_WAVE,      ///< @see Wave
    RM_SOUND,     ///< @see Sound
    RM_MUSIC,     ///< @see Music
} rmResourceType;

/**
 * @brief The Resource data union (all the possible resource data types)
 */
typedef union
{
    Image Image;         ///< @see Image
    Texture2D Texture2D; ///< @see Texture2D
    Font Font;           ///< @see Font
    Wave Wave;           ///< @see Wave
    Sound Sound;         ///< @see Sound
    Music Music;         ///< @see Music
} rmResource_u;

/**
 * @brief The Resource Data Structure:
 */
struct rmResource_t
{
    char name[100];      ///< Key value for the HashMap
    rmResourceType type; ///< The Resource Type
    char path[100];      ///< The Resource file path
    rmResource_u data;   ///< The Resource data union
    UT_hash_handle hh;   ///< Hash handler for the uthash library
};

/**
 * @brief Initialize the ResourceManager HashMap @see rmMap
 *
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int rmInit();

/**
 * @brief adds a resource of the specified name, type and path to the rmMap HashMap
 *
 * @param type the type of the Resource to get @see rmResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see rmResource_t
 * @param path the relative path to the Resource file, from the executable location
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int rmAddResource(rmResourceType type, const char *name, const char *path);

/**
 * @brief removes a resource of the specified name and type from the rmMap HashMap
 *
 * @param type the type of the Resource to get @see rmResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see rmResource_t
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int rmRemoveResource(rmResourceType type, const char *name);

/**
 * @brief iterates through Resource HashMap and call the exact Raylib Load function for each Resource Type
 *
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int rmLoad();

/**
 * @brief gets a pointer to the resource data of the specified rmResourceType after being loaded through rmLoad()
 * @param type the type of the Resource to get @see rmResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see rmResource_t
 * @return void*
 */
void *rmGet(rmResourceType type, const char *name);

/**
 * @brief iterates through Resource HashMap and call the exact Raylib Unload function for each Resource Type
 *
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int rmUnload();

/**
 * @brief iterates through Resource HashMap, dereference HashMap elements and frees memory
 *
 * @return int APP_ERROR or APP_WARNING or APP_SUCCESS
 */
int rmDestroy();

#endif /* __RESOURCEMANAGER_H__ */
