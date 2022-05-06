#include "SceneManager.h"
#include "logger.h"

#include <string.h>

#ifdef LOG_STYLE_USE_COLOR
#define SCENE_MANAGER_PREFIX "\033[33m[SceneManager]\033[0m "
#else
#define SCENE_MANAGER_PREFIX "[SceneManager] "
#endif // LOG_STYLE_USE_COLOR

int SceneManagerInit()
{
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Initializing Scene Manager...");

    SceneManager.attr.currentScene = NULL;
    SceneManager.attr.nextScene = NULL;
    SceneManager.attr.isSceneEnded = false;
    
    // sets scene manager map to NULL, it's required by uthash lib
	SceneManagerSceneMap = NULL;
}

int SceneManagerRegister(const char *name, struct Scene_t *scene)
{
    struct Scene_t *s;
    HASH_FIND_STR(SceneManagerSceneMap, name, s);

    if(s == NULL)
    {
        //if the scene was not registered yet adds the scene to the scene map
        Log(LOG_INFO, SCENE_MANAGER_PREFIX "Adding scene %s to Scene Manager...", scene->name);
        HASH_ADD_STR(SceneManagerSceneMap, name, scene);
    }
    else
    {
        //if the scene was not registered yet adds the scene to the scene map
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Scene %s yet exists in Scene Manager!", scene->name);
        return APP_ERROR;
    }

    return APP_SUCCESS;
}

int SceneManagerStart(const char *firstSceneName)
{
    struct Scene_t *s;
    HASH_FIND_STR(SceneManagerSceneMap, firstSceneName, s);

    // if scene is not registered print error and return error code
    if(s == NULL)
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Can't start Scene Manager, %s scene doesn't exist!");
        return APP_ERROR;
    }

    // sets the next scene to the given first scene and starts Scene Manager's loop
    SceneManager.Next(firstSceneName);
    SceneManagerLoop();

	return APP_SUCCESS;
}

double SceneManagerTime()
{
    if (SceneManager.attr.currentScene != NULL)
    {
        // if there's a scene running returns the current time minus the time the scene was setted
        return GetTime() - SceneManager.attr.currentScene->setupTime;
    }
    else
    {
        // if there's no scene running prints error
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Can't get Scene time, there's no scene currently running!");
    }
}

int SceneManagerNext(const char *name)
{
    struct Scene_t *s;
    HASH_FIND_STR(SceneManagerSceneMap, name, s);

    // if can't find scene in the hasmap and name is not "END" ("END" is used to stop SceneManager)
    if(s == NULL && !strcmp(name, "END"))
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Unable to set next scene to %n, scene doesn't exists", name);
        return APP_ERROR;
    }

    //set next scene to the given one or NULL in case name == "END" (this will make the SceneManager close after last cycle)
    SceneManager.attr.nextScene = s;
    SceneManager.attr.isSceneEnded = true;

	return APP_SUCCESS;
}


int SceneManagerLoop()
{
    while ( !WindowShouldClose() || !SceneManager.attr.isSceneEnded || SceneManager.attr.nextScene != NULL)
    {
        // set next scene as current
        SceneManager.attr.currentScene = SceneManager.attr.nextScene;
        SceneManager.attr.nextScene = NULL;
        SceneManager.attr.isSceneEnded = false;

        // setup and start current scene
        SceneManager.attr.currentScene->setupTime = GetTime();
        SceneManager.attr.currentScene->Setup();
        SceneManager.attr.currentScene->Start();
        while (!SceneManager.attr.isSceneEnded)
        {
            SceneManager.attr.currentScene->Update();
            SceneManager.attr.currentScene->FixedUpdate(); // TODO: make fixedUpdate being called every idk
            SceneManager.attr.currentScene->Render();
        }
        SceneManager.attr.currentScene->Exit();
    }

    SceneManagerEnd();
    return APP_SUCCESS;
}

int SceneManagerEnd()
{
    struct Scene_t *res, *tmp;
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Cleaning scene table...");

    HASH_ITER(hh, SceneManagerSceneMap, res, tmp) // iterates the full scene HashMap
    {
        Log(LOG_DEBUG, SCENE_MANAGER_PREFIX "Removing %s scene \"%s\"", res->name);
        HASH_DEL(SceneManagerSceneMap, res); // removes scene from the scene HashMap
    }

    SceneManager.attr.currentScene = NULL;
    SceneManager.attr.nextScene = NULL;
    SceneManager.attr.isSceneEnded = false;
    return APP_SUCCESS;
}
