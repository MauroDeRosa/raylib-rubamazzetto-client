#include "ResourceManager.h"
#include "logger.h"

#include <string.h>

#ifdef LOG_STYLE_USE_COLOR
#define RESOURCE_MANAGER_PREFIX "\033[33m[ResourceManager]\033[0m "
#else
#define RESOURCE_MANAGER_PREFIX "[ResourceManager] "
#endif // LOG_STYLE_USE_COLOR

int __ResourceManagerInit()
{
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Initializing Resource Manager...");
    __ResourceManagerMap = NULL; // sets Resource HashMap to NULL (required by uthash as initial HashMap pointer value)
    return RESOURCE_MANAGER_SUCCESS;
}

int __ResourceManagerAddResource(ResourceType type, const char *name, const char *path)
{
    char *fullName = __ResourceManagerGetResourceName(type, name); // creates temporary variable containing "ResourceType_name"
    struct __Resource_t *res = __ResourceManagerGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res == NULL) // if resource named ResourceType_name is not in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Adding %s resource \"%s\" path: \"%s\"", __ResourceTypeString[type], name, path);
        res = malloc(sizeof(*res)); // allocates memory for the given resource (__Resource_t)
        strcpy(res->name, fullName); // sets Resource HashMap item key to ResourceType_name
        res->type = type; //sets ResourceType to the given type
        HASH_ADD_STR(__ResourceManagerMap, name, res); // adds the Resource to the Resource HashMap
    }
    else // if resource named ResourceType_name is yet in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Updating %s resource \"%s\" path: \"%s\"", __ResourceTypeString[type], name, path);
    }

    // TODO: check if the path is correct
    strcpy(res->path, path); // sets Resource path or updates it
    free(fullName); // free temporary variable containing "ResourceType_name"
    return RESOURCE_MANAGER_SUCCESS;
}

int __ResourceManagerRemoveResource(ResourceType type, const char *name)
{
    char *fullName = __ResourceManagerGetResourceName(type, name); // creates temporary variable containing "ResourceType_name"
    struct __Resource_t *res = __ResourceManagerGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res != NULL) // if resource named ResourceType_name is in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Removing %s resource \"%s\" path: \"%s\"", __ResourceTypeString[type], name, res->path);
        HASH_DEL(__ResourceManagerMap, res); // removes 'ResourceType_name' from the Resource HashMap
        free(res); // free memory of the resource remove from the Resource HashMap (__Resource_t)
        return RESOURCE_MANAGER_SUCCESS;
    }
    else // if resource named ResourceType_name is not in the Resource HashMap
    {
        Log(LOG_WARNING, RESOURCE_MANAGER_PREFIX "Can't remove %s resurce named \"%s\", resource doesn't exist", __ResourceTypeString[type], name);
        return RESOURCE_MANAGER_WARNING;
    }

    free(fullName); // free temporary variable containing "ResourceType_name"
}

int __ResourceManagerLoad()
{
    struct __Resource_t *res, *tmp;
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Loading resources...");

    HASH_ITER(hh, __ResourceManagerMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RESOURCE_MANAGER_PREFIX "Loading %s resource \"%s\"", __ResourceTypeString[res->type], res->name);

        switch (res->type) // based on the resource type calls the right RayLib Load function and sets data.ResourceType with it
        {
            case RESOURCE_IMAGE:
                res->data.Image = LoadImage(res->path);
                break;
            case RESOURCE_TEXTURE2D:
                res->data.Texture2D = LoadTexture(res->path);
                break;
            case RESOURCE_FONT:
                res->data.Font = LoadFont(res->path);
                break;
            case RESOURCE_WAVE:
                res->data.Wave = LoadWave(res->path);
                break;
            case RESOURCE_SOUND:
                res->data.Sound = LoadSound(res->path);
                break;
            case RESOURCE_MUSIC:
                res->data.Music = LoadMusicStream(res->path);
                break;
        }
    }

    return RESOURCE_MANAGER_SUCCESS;
}

void *__ResourceManagerGet(ResourceType type, const char *name)
{
    char *fullName = __ResourceManagerGetResourceName(type, name); // creates temporary variable containing "ResourceType_name"
    struct __Resource_t *res = __ResourceManagerGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res != NULL) // if resource named ResourceType_name is in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Getting %s resource \"%s\"", __ResourceTypeString[type], name);
        return __ResourceManagerGetResourceDataPointer(res); // returns a void* pointer to the resource data.ResourceType
    }
    else // if resource named ResourceType_name is not in the Resource HashMap
    {
        Log(LOG_WARNING, RESOURCE_MANAGER_PREFIX "Can't get %s resurce named \"%s\", resource doesn't exist", __ResourceTypeString[type], name);
        return NULL; // returns NULL to indicate that the Resource doesn't exists
    }

    free(fullName);
}

int __ResourceManagerUnload()
{
    struct __Resource_t *res, *tmp;
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Unloading resources...");

    HASH_ITER(hh, __ResourceManagerMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RESOURCE_MANAGER_PREFIX "Unloading %s resource \"%s\"", __ResourceTypeString[res->type], res->name);

        switch (res->type) // based on the resource type calls the right RayLib Unload function
        {
            case RESOURCE_IMAGE:
                UnloadImage(res->data.Image);
                break;
            case RESOURCE_TEXTURE2D:
                UnloadTexture(res->data.Texture2D);
                break;
            case RESOURCE_FONT:
                UnloadFont(res->data.Font);
                break;
            case RESOURCE_WAVE:
                UnloadWave(res->data.Wave);
                break;
            case RESOURCE_SOUND:
                UnloadSound(res->data.Sound);
                break;
            case RESOURCE_MUSIC:
                UnloadMusicStream(res->data.Music);
                break;
        }
    }

    return RESOURCE_MANAGER_SUCCESS;
}

int __ResourceManagerDestroy()
{
    struct __Resource_t *res, *tmp;
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Cleaning resource table...");

    HASH_ITER(hh, __ResourceManagerMap, res, tmp)
    {
        Log(LOG_DEBUG, RESOURCE_MANAGER_PREFIX "Removing %s resource \"%s\"", __ResourceTypeString[res->type], res->name);
        free(res);
    }

    return RESOURCE_MANAGER_SUCCESS;
}

char *__ResourceManagerGetResourceName(ResourceType type, const char *name)
{
    char *out = calloc(100, sizeof(char));
    strcat(out, __ResourceTypeString[type]);
    strcat(out, "_");
    strcat(out, name);
    return out;
}

struct __Resource_t *__ResourceManagerGetResourcePointer(char* fullName)
{
    struct __Resource_t *res = NULL;
    HASH_FIND_STR(__ResourceManagerMap, fullName, res);
    return res;
}

void *__ResourceManagerGetResourceDataPointer(struct __Resource_t *resource)
{
    if(resource == NULL) return NULL;

    switch (resource->type)
    {
    case RESOURCE_IMAGE:
        return &(resource->data.Image);
        break;
    case RESOURCE_TEXTURE2D:
        return &(resource->data.Texture2D);
        break;
    case RESOURCE_FONT:
        return &(resource->data.Font);
        break;
    case RESOURCE_WAVE:
        return &(resource->data.Wave);
        break;
    case RESOURCE_SOUND:
        return &(resource->data.Sound);
        break;
    case RESOURCE_MUSIC:
        return &(resource->data.Music);
        break;
    }
}