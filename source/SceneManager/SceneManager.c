#include "SceneManager/SceneManager.h"
#include "utils/logger.h"

#include <string.h>

#define SCENE_MANAGER_PREFIX LOG_COLOR_YELLOW "[SceneManager] " LOG_COLOR_RESET

#define SCENE_MANAGER_FIXED_TIME_STEP (1.0f / 2.0f)

SceneManager_t SceneManager = {
    (SceneManagerAttribute_t){ NULL, NULL, NULL, false, 0},     ///< @see SceneManagerAttribute_t
    SceneManagerInit,                                           ///< @see SceneManagerInit
    SceneManagerRegister,                                       ///< @see SceneManagerRegister
    SceneManagerStart,                                          ///< @see SceneManagerStart
    SceneManagerTime,                                           ///< @see SceneManagerTime
    SceneManagerNext                                            ///< @see SceneManagerNext
};

int SceneManagerInit()
{
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Initializing Scene Manager...");

    SceneManager.attr.currentScene = NULL;
    SceneManager.attr.nextScene = NULL;
    SceneManager.attr.isSceneEnded = false;
    SceneManager.attr.fixedStepTimer = 0.0f;
    
    // sets scene manager map to NULL, it's required by uthash lib
	SceneManager.attr.map = NULL;
}

int SceneManagerRegister(const char *name, struct Scene_t *scene)
{
    struct Scene_t *s = NULL;
    HASH_FIND_STR(SceneManager.attr.map, name, s);

    if(s == NULL)
    {
        //if the scene was not registered yet adds the scene to the scene map
        Log(LOG_INFO, SCENE_MANAGER_PREFIX "Adding scene %s to Scene Manager...", scene->name);
        HASH_ADD_STR(SceneManager.attr.map, name, scene);
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
    HASH_FIND_STR(SceneManager.attr.map, firstSceneName, s);

    // if scene is not registered print error and return error code
    if(s == NULL)
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Can't start Scene Manager, %s scene doesn't exist!", firstSceneName);
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
        return GetTime() - SceneManager.attr.currentScene->startTime;
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
    HASH_FIND_STR(SceneManager.attr.map, name, s);

    // if can't find scene in the hasmap and name is not "END" ("END" is used to stop SceneManager)
    if(s == NULL && strcmp(name, "END") != 0)
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Unable to set next scene to %s, scene doesn't exists", name);
        return APP_ERROR;
    }

    //set next scene to the given one or NULL in case name == "END" (this will make the SceneManager close after last cycle)
    SceneManager.attr.nextScene = s;
    SceneManager.attr.isSceneEnded = true;

	return APP_SUCCESS;
}

int SceneManagerLoop()
{
    while (!SceneManager.attr.isSceneEnded || SceneManager.attr.nextScene != NULL)
    {
        // set next scene as current
        SceneManager.attr.currentScene = SceneManager.attr.nextScene;
        SceneManager.attr.nextScene = NULL;
        SceneManager.attr.isSceneEnded = false;
        SceneManager.attr.fixedStepTimer = 0;

        // setup and start current scene
        SceneManager.attr.currentScene->startTime = GetTime();
        SceneManager.attr.currentScene->Start();
        while (!SceneManager.attr.isSceneEnded)
        {
            SceneManager.attr.fixedStepTimer += GetFrameTime();
            SceneManager.attr.currentScene->Update();

            if(SceneManager.attr.fixedStepTimer > SCENE_MANAGER_FIXED_TIME_STEP)
            {
                SceneManager.attr.currentScene->FixedUpdate();
                SceneManager.attr.fixedStepTimer = 0;
            }
            
            BeginDrawing();
            ClearBackground(BLACK);
            SceneManager.attr.currentScene->Render();
            EndDrawing();

            if (WindowShouldClose())
            {
                SceneManager.Next("END");
            }
            
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

    HASH_ITER(hh, SceneManager.attr.map, res, tmp) // iterates the full scene HashMap
    {
        Log(LOG_DEBUG, SCENE_MANAGER_PREFIX "Removing %s scene", res->name);
        HASH_DEL(SceneManager.attr.map, res); // removes scene from the scene HashMap
    }

    SceneManager.attr.currentScene = NULL;
    SceneManager.attr.nextScene = NULL;
    SceneManager.attr.isSceneEnded = false;
    return APP_SUCCESS;
}
