#include "ResourceManager/ResourceManager.h"
#include "utils/logger.h"

#include <string.h>
#include "Config.h"

#define RESOURCE_MANAGER_PREFIX LOG_COLOR_YELLOW "[ResourceManager] " LOG_COLOR_RESET

int ResourceManagerInit()
{
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Initializing Resource Manager...");
    __ResourceManagerMap = NULL; // sets Resource HashMap to NULL (required by uthash as initial HashMap pointer value)
    return APP_SUCCESS;
}

int ResourceManagerAddResource(ResourceType type, const char *name, const char *path)
{
    char *fullName = ResourceManagerGetResourceName(type, name); // creates temporary variable containing "ResourceType_name"
    
    struct Resource_t *res = ResourceManagerGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res == NULL) // if resource named ResourceType_name is not in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Adding %s resource \"%s\" path: \"%s\"", ResourceTypeString[type], name, path);
        res = malloc(sizeof(*res)); // allocates memory for the given resource (Resource_t)
        strcpy(res->name, fullName); // sets Resource HashMap item key to ResourceType_name
        res->type = type; //sets ResourceType to the given type
        HASH_ADD_STR(__ResourceManagerMap, name, res); // adds the Resource to the Resource HashMap
    }
    else // if resource named ResourceType_name is yet in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Updating %s resource \"%s\" path: \"%s\"", ResourceTypeString[type], name, path);
    }

    strcpy(res->path, path); // sets Resource path or updates it
    free(fullName); // free temporary variable containing "ResourceType_name"
    return APP_SUCCESS;
}

int ResourceManagerRemoveResource(ResourceType type, const char *name)
{
    char *fullName = ResourceManagerGetResourceName(type, name); // creates temporary variable containing "ResourceType_name"
    struct Resource_t *res = ResourceManagerGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res != NULL) // if resource named ResourceType_name is in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Removing %s resource \"%s\" path: \"%s\"", ResourceTypeString[type], name, res->path);
        HASH_DEL(__ResourceManagerMap, res); // removes 'ResourceType_name' from the Resource HashMap
        free(res); // free memory of the resource removed from the Resource HashMap (Resource_t)
        return APP_SUCCESS;
    }
    else // if resource named ResourceType_name is not in the Resource HashMap
    {
        Log(LOG_WARNING, RESOURCE_MANAGER_PREFIX "Can't remove %s resurce named \"%s\", resource doesn't exist", ResourceTypeString[type], name);
        return APP_WARNING;
    }

    free(fullName); // free temporary variable containing "ResourceType_name"
}

int ResourceManagerLoad()
{
    struct Resource_t *res, *tmp;
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Loading resources...");

    HASH_ITER(hh, __ResourceManagerMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RESOURCE_MANAGER_PREFIX "Loading %s resource \"%s\"", ResourceTypeString[res->type], res->name);

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

    return APP_SUCCESS;
}

void *ResourceManagerGet(ResourceType type, const char *name)
{
    char *fullName = ResourceManagerGetResourceName(type, name); // creates temporary variable containing "ResourceType_name"
    struct Resource_t *res = ResourceManagerGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res != NULL) // if resource named ResourceType_name is in the Resource HashMap
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Getting %s resource \"%s\"", ResourceTypeString[type], name);
        return ResourceManagerGetResourceDataPointer(res); // returns a void* pointer to the resource data.ResourceType
    }
    else // if resource named ResourceType_name is not in the Resource HashMap
    {
        Log(LOG_WARNING, RESOURCE_MANAGER_PREFIX "Can't get %s resurce named \"%s\", resource doesn't exist", ResourceTypeString[type], name);
        return NULL; // returns NULL to indicate that the Resource doesn't exists
    }

    free(fullName);
}

int ResourceManagerUnload()
{
    struct Resource_t *res, *tmp;
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Unloading resources...");

    HASH_ITER(hh, __ResourceManagerMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RESOURCE_MANAGER_PREFIX "Unloading %s resource \"%s\"", ResourceTypeString[res->type], res->name);

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

    return APP_SUCCESS;
}

int ResourceManagerDestroy()
{
    struct Resource_t *res, *tmp;
    Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Cleaning resource table...");

    HASH_ITER(hh, __ResourceManagerMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RESOURCE_MANAGER_PREFIX "Removing %s resource \"%s\"", ResourceTypeString[res->type], res->name);
        HASH_DEL(__ResourceManagerMap, res); // removes 'ResourceType_name' from the Resource HashMap
        free(res); // free memory of the resource removed from the Resource HashMap (Resource_t)
    }

    return APP_SUCCESS;
}

char *ResourceManagerGetResourceName(ResourceType type, const char *name)
{
    char *out = calloc(100, sizeof(char));
    strcat(out, ResourceTypeString[type]);
    strcat(out, "_");
    strcat(out, name);
    out[100-1] = '\0';
    return out; // returns "ResourceType_name"
}

struct Resource_t *ResourceManagerGetResourcePointer(char* fullName)
{
    struct Resource_t *res = NULL;
    HASH_FIND_STR(__ResourceManagerMap, fullName, res); // returns *Resource_t if 'ResourceType_name' exists, NULL otherwise
    return res;
}

void *ResourceManagerGetResourceDataPointer(struct Resource_t *resource)
{
    if(resource == NULL) return NULL;

    switch (resource->type) // based on ResourceType returns pointer to resource's data.DataType
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