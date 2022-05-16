#include "ResourceManager/ResourceManager.h"
#include "utils/logger.h"

#include <stdatomic.h>
#include <pthread.h>
#include <string.h>
#include "Config.h"
#include "gui/gui.h"

// TODO: PLS FIX DOCUMENTATION

#define RM_LOG_PREFIX LOG_COLOR_YELLOW "[ResourceManager] " LOG_COLOR_RESET

/**
 * @brief The string representation of the Resource Type
 */
const char *rmResourceTypeString[] = {
    "Image",     ///< @see Image
    "Texture2D", ///< @see Texture2D
    "Font",      ///< @see Font
    "Wave",      ///< @see Wave
    "Sound",     ///< @see Sound
    "Music"      ///< @see Music
};

struct rmResource_t *rmMap = NULL;

static atomic_bool isLoaded = ATOMIC_VAR_INIT(false);
static atomic_uint progress = ATOMIC_VAR_INIT(0);
pthread_t loadThreadId;
static void *rmLoadThread(void *arg);

/**
 * @brief Get a string in the form "rmResourceType_name"
 *
 * @param type the type of the Resource to get @see rmResourceType
 * @param name the name of the resource to get (key value of the Resource HashMap element) @see rmResource_t
 * @return char* a string containing "rmResourceType_name" (must be freed) @see rmResourceType @see rmResource_t
 */
char *rmGetResourceName(rmResourceType type, const char *name);

/**
 * @brief
 *
 * @param fullName A string in the form "rmResourceType_name" used as key value in the rmMap HashMap
 * @return struct rmResource_t* The pointer to the Resource element found in Hasmap. NULL if nothing was found @see rmResource_t
 */
struct rmResource_t *rmGetResourcePointer(char *fullName);

/**
 * @brief
 *
 * @param resource
 * @return void*
 */
void *rmGetResourceDataPointer(struct rmResource_t *resource);


int rmInit()
{
    Log(LOG_INFO, RM_LOG_PREFIX "Initializing Resource Manager...");
    rmMap = NULL; // sets Resource HashMap to NULL (required by uthash as initial HashMap pointer value)
    return APP_SUCCESS;
}

int rmAddResource(rmResourceType type, const char *name, const char *path)
{
    char *fullName = rmGetResourceName(type, name); // creates temporary variable containing "rmResourceType_name"

    struct rmResource_t *res = rmGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res == NULL) // if resource named rmResourceType_name is not in the Resource HashMap
    {
        Log(LOG_INFO, RM_LOG_PREFIX "Adding %s resource \"%s\" path: \"%s\"", rmResourceTypeString[type], name, path);
        res = malloc(sizeof(*res));     // allocates memory for the given resource (rmResource_t)
        strcpy(res->name, fullName);    // sets Resource HashMap item key to rmResourceType_name
        res->type = type;               // sets rmResourceType to the given type
        HASH_ADD_STR(rmMap, name, res); // adds the Resource to the Resource HashMap
    }
    else // if resource named rmResourceType_name is yet in the Resource HashMap
    {
        Log(LOG_INFO, RM_LOG_PREFIX "Updating %s resource \"%s\" path: \"%s\"", rmResourceTypeString[type], name, path);
    }

    strcpy(res->path, path); // sets Resource path or updates it
    free(fullName);          // free temporary variable containing "rmResourceType_name"
    return APP_SUCCESS;
}

int rmRemoveResource(rmResourceType type, const char *name)
{
    char *fullName = rmGetResourceName(type, name);            // creates temporary variable containing "rmResourceType_name"
    struct rmResource_t *res = rmGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res != NULL) // if resource named rmResourceType_name is in the Resource HashMap
    {
        Log(LOG_INFO, RM_LOG_PREFIX "Removing %s resource \"%s\" path: \"%s\"", rmResourceTypeString[type], name, res->path);
        HASH_DEL(rmMap, res); // removes 'rmResourceType_name' from the Resource HashMap
        free(res);            // free memory of the resource removed from the Resource HashMap (rmResource_t)
        return APP_SUCCESS;
    }
    else // if resource named rmResourceType_name is not in the Resource HashMap
    {
        Log(LOG_WARNING, RM_LOG_PREFIX "Can't remove %s resurce named \"%s\", resource doesn't exist", rmResourceTypeString[type], name);
        return APP_WARNING;
    }

    free(fullName); // free temporary variable containing "rmResourceType_name"
}

void rmLoad()
{
    int error = pthread_create(&loadThreadId, NULL, rmLoadThread, NULL);
    if (error != 0)
    {
        Log(LOG_ERROR, "Error creating loading thread");
    }
    else
    {
        Log(LOG_INFO, "Loading thread initialized successfully");
    }

    uiCarpetInit();
}

static void *rmLoadThread(void *arg)
{
    struct rmResource_t *res, *tmp;
    Log(LOG_INFO, RM_LOG_PREFIX "Loading resources...");

    // TODO: load user file
    // TODO: load match log file

    int toLoadCount = HASH_COUNT(rmMap);
    float percentage = 0.0f;



    HASH_ITER(hh, rmMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RM_LOG_PREFIX "Loading %s resource \"%s\"", rmResourceTypeString[res->type], res->name);

        switch (res->type) // based on the resource type calls the right RayLib Load function and sets data.rmResourceType with it
        {
        case RM_IMAGE:
            res->data.Image = LoadImage(res->path);
            break;
        case RM_TEXTURE2D:
            res->data.Image = LoadImage(res->path); // can't use glContext out of main thread to do GPU operations
            break;
        case RM_FONT:
            res->data.Font = LoadFont(res->path);
            break;
        case RM_WAVE:
            res->data.Wave = LoadWave(res->path);
            break;
        case RM_SOUND:
            res->data.Sound = LoadSound(res->path);
            break;
        case RM_MUSIC:
            res->data.Music = LoadMusicStream(res->path);
            break;
        }
        
        percentage += (100.0f/toLoadCount);
        atomic_store(&progress, (unsigned int)(percentage) );
    }

    atomic_store(&isLoaded, true);
}

void *rmGet(rmResourceType type, const char *name)
{
    char *fullName = rmGetResourceName(type, name);            // creates temporary variable containing "rmResourceType_name"
    struct rmResource_t *res = rmGetResourcePointer(fullName); // check if resource exists in hashmap otherwise returns NULL

    if (res != NULL) // if resource named rmResourceType_name is in the Resource HashMap
    {
        Log(LOG_DEBUG, RM_LOG_PREFIX "Getting %s resource \"%s\"", rmResourceTypeString[type], name);
        return rmGetResourceDataPointer(res); // returns a void* pointer to the resource data.rmResourceType
    }
    else // if resource named rmResourceType_name is not in the Resource HashMap
    {
        Log(LOG_WARNING, RM_LOG_PREFIX "Can't get %s resurce named \"%s\", resource doesn't exist", rmResourceTypeString[type], name);
        return NULL; // returns NULL to indicate that the Resource doesn't exists
    }

    free(fullName);
}

int rmUnload()
{
    struct rmResource_t *res, *tmp;
    Log(LOG_INFO, RM_LOG_PREFIX "Unloading resources...");

    HASH_ITER(hh, rmMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RM_LOG_PREFIX "Unloading %s resource \"%s\"", rmResourceTypeString[res->type], res->name);

        switch (res->type) // based on the resource type calls the right RayLib Unload function
        {
        case RM_IMAGE:
            UnloadImage(res->data.Image);
            break;
        case RM_TEXTURE2D:
            UnloadImage(res->data.Image);
            break;
        case RM_FONT:
            UnloadFont(res->data.Font);
            break;
        case RM_WAVE:
            UnloadWave(res->data.Wave);
            break;
        case RM_SOUND:
            UnloadSound(res->data.Sound);
            break;
        case RM_MUSIC:
            UnloadMusicStream(res->data.Music);
            break;
        }
    }

    uiCarpetUnload();

    return APP_SUCCESS;
}

int rmDestroy()
{
    struct rmResource_t *res, *tmp;
    Log(LOG_INFO, RM_LOG_PREFIX "Cleaning resource table...");

    HASH_ITER(hh, rmMap, res, tmp) // iterates the full Resource HashMap
    {
        Log(LOG_DEBUG, RM_LOG_PREFIX "Removing %s resource \"%s\"", rmResourceTypeString[res->type], res->name);
        HASH_DEL(rmMap, res); // removes 'rmResourceType_name' from the Resource HashMap
        free(res);            // free memory of the resource removed from the Resource HashMap (rmResource_t)
    }

    return APP_SUCCESS;
}

char *rmGetResourceName(rmResourceType type, const char *name)
{
    char *out = calloc(100, sizeof(char));
    strcat(out, rmResourceTypeString[type]);
    strcat(out, "_");
    strcat(out, name);
    out[100 - 1] = '\0';
    return out; // returns "rmResourceType_name"
}

struct rmResource_t *rmGetResourcePointer(char *fullName)
{
    struct rmResource_t *res = NULL;
    HASH_FIND_STR(rmMap, fullName, res); // returns *rmResource_t if 'rmResourceType_name' exists, NULL otherwise
    return res;
}

void *rmGetResourceDataPointer(struct rmResource_t *resource)
{
    if (resource == NULL)
        return NULL;

    switch (resource->type) // based on rmResourceType returns pointer to resource's data.DataType
    {
    case RM_IMAGE:
        return &(resource->data.Image);
        break;
    case RM_TEXTURE2D:
        if(resource->isTextureConverted == false)
        {
            resource->convertedTexture = LoadTextureFromImage(resource->data.Image);
            resource->isTextureConverted = true;
        }
        return &(resource->convertedTexture);
        break;
    case RM_FONT:
        return &(resource->data.Font);
        break;
    case RM_WAVE:
        return &(resource->data.Wave);
        break;
    case RM_SOUND:
        return &(resource->data.Sound);
        break;
    case RM_MUSIC:
        return &(resource->data.Music);
        break;
    }
}

bool rmGetIsLoaded()
{
    return atomic_load(&isLoaded);
}

float rmGetProgress()
{
    return atomic_load(&progress) / 100.0f;
}