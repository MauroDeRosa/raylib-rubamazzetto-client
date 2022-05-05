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
    __ResourceManagerMap = NULL;
    return RESOURCE_MANAGER_SUCCESS;
}


int __ResourceManagerAddResource(ResourceType type, const char *name, const char *path)
{
    struct __Resource_t *res = NULL;
    char *fullName = __ResourceManagerGetResourceName(type, name);

    HASH_FIND_STR(__ResourceManagerMap, fullName, res);

    if (res == NULL)
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Adding %s resource \"%s\" path: \"%s\"", __ResourceTypeString[type], name, path);
        res = malloc(sizeof(*res));
        strcpy(res->name, fullName);
        res->type = type;
        HASH_ADD_STR(__ResourceManagerMap, name, res);
    }
    else
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Updating %s resource \"%s\" path: \"%s\"", __ResourceTypeString[type], name, path);
    }

    strcpy(res->path, path);
    free(fullName);
    return RESOURCE_MANAGER_SUCCESS;
}

int __ResourceManagerRemoveResource(ResourceType type, const char *name)
{
    struct __Resource_t *res = NULL;
    char* fullName = __ResourceManagerGetResourceName(type, name);
    HASH_FIND_STR(__ResourceManagerMap, fullName , res);

    if(res != NULL)
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Removing %s resource \"%s\" path: \"%s\"", __ResourceTypeString[type], name, res->path);
        HASH_DEL(__ResourceManagerMap, res);
        free(res);
        return RESOURCE_MANAGER_SUCCESS;
    }
    else
    {
        Log(LOG_WARNING, RESOURCE_MANAGER_PREFIX "Can't remove %s resurce named \"%s\", resource doesn't exist", __ResourceTypeString[type], name);
        return RESOURCE_MANAGER_WARNING;
    }

    free(fullName);
}

int __ResourceManagerLoad()
{
    
}

void *__ResourceManagerGet(ResourceType type, const char *name)
{
    struct __Resource_t *res = NULL;
    char* fullName = __ResourceManagerGetResourceName(type, name);
    HASH_FIND_STR(__ResourceManagerMap, fullName , res);

    if(res != NULL)
    {
        Log(LOG_INFO, RESOURCE_MANAGER_PREFIX "Getting %s resource \"%s\"", __ResourceTypeString[type], name);
        return &res->resource;
    }
    else
    {
        Log(LOG_WARNING, RESOURCE_MANAGER_PREFIX "Can't remove %s resurce named \"%s\", resource doesn't exist", __ResourceTypeString[type], name);
        return NULL;
    }

    free(fullName);
}

int __ResourceManagerUnload()
{
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
    char* out = calloc(100, sizeof(char));
    strcat(out, __ResourceTypeString[type]);
    strcat(out, "_");
    strcat(out, name);
    return out;
}

int __ResourceManagerExists(ResourceType type, const char *name)
{

}

void *__ResourceManagerGetResourcePointer(struct __Resource_t *resource)
{
    
}