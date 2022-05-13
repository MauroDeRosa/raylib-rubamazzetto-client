#include "SceneManager/SceneManager.h"
#include "utils/logger.h"

#include <string.h>

#define SM_LOG_PREFIX LOG_COLOR_YELLOW "[SceneManager] " LOG_COLOR_RESET

#define SM_FIXED_TIME_STEP (1.0f / 2.0f)

smData_t smData;

int smInit()
{
    Log(LOG_INFO, SM_LOG_PREFIX "Initializing Scene Manager...");

    smData.currentScene = NULL;
    smData.nextScene = NULL;
    smData.isSceneEnded = false;
    smData.fixedStepTimer = 0.0f;
    
    // sets scene manager map to NULL, it's required by uthash lib
	smData.map = NULL;
}

int smRegister(const char *name, struct Scene_t *scene)
{
    struct Scene_t *s = NULL;
    HASH_FIND_STR(smData.map, name, s);

    if(s == NULL)
    {
        //if the scene was not registered yet adds the scene to the scene map
        Log(LOG_INFO, SM_LOG_PREFIX "Adding scene %s to Scene Manager...", scene->name);
        HASH_ADD_STR(smData.map, name, scene);
    }
    else
    {
        //if the scene was not registered yet adds the scene to the scene map
        Log(LOG_ERROR, SM_LOG_PREFIX "Scene %s yet exists in Scene Manager!", scene->name);
        return APP_ERROR;
    }

    return APP_SUCCESS;
}

int smStart(const char *firstSceneName)
{
    struct Scene_t *s;
    HASH_FIND_STR(smData.map, firstSceneName, s);

    // if scene is not registered print error and return error code
    if(s == NULL)
    {
        Log(LOG_ERROR, SM_LOG_PREFIX "Can't start Scene Manager, %s scene doesn't exist!", firstSceneName);
        return APP_ERROR;
    }

    // sets the next scene to the given first scene and starts Scene Manager's loop
    smNext(firstSceneName);
    smLoop();

	return APP_SUCCESS;
}

double smTime()
{
    if (smData.currentScene != NULL)
    {
        // if there's a scene running returns the current time minus the time the scene was setted
        return GetTime() - smData.currentScene->startTime;
    }
    else
    {
        // if there's no scene running prints error
        Log(LOG_ERROR, SM_LOG_PREFIX "Can't get Scene time, there's no scene currently running!");
    }
}

int smNext(const char *name)
{
    struct Scene_t *s;
    HASH_FIND_STR(smData.map, name, s);

    // if can't find scene in the hasmap and name is not "END" ("END" is used to stop SceneManager)
    if(s == NULL && strcmp(name, "END") != 0)
    {
        Log(LOG_ERROR, SM_LOG_PREFIX "Unable to set next scene to %s, scene doesn't exists", name);
        return APP_ERROR;
    }

    //set next scene to the given one or NULL in case name == "END" (this will make the SceneManager close after last cycle)
    smData.nextScene = s;
    smData.isSceneEnded = true;

	return APP_SUCCESS;
}

int smLoop()
{
    while (!smData.isSceneEnded || smData.nextScene != NULL)
    {
        // set next scene as current
        smData.currentScene = smData.nextScene;
        smData.nextScene = NULL;
        smData.isSceneEnded = false;
        smData.fixedStepTimer = 0;

        // setup and start current scene
        smData.currentScene->startTime = GetTime();
        smData.currentScene->Start();
        while (!smData.isSceneEnded)
        {
            smData.fixedStepTimer += GetFrameTime();
            smData.currentScene->Update();

            if(smData.fixedStepTimer > SM_FIXED_TIME_STEP)
            {
                smData.currentScene->FixedUpdate();
                smData.fixedStepTimer = 0;
            }
            
            BeginDrawing();
            ClearBackground(BLACK);
            smData.currentScene->Render();
            EndDrawing();

            if (WindowShouldClose())
            {
                smNext("END");
            }
            
        }
        smData.currentScene->Exit();
    }

    smEnd();
    return APP_SUCCESS;
}

int smEnd()
{
    struct Scene_t *res, *tmp;
    Log(LOG_INFO, SM_LOG_PREFIX "Cleaning scene table...");

    HASH_ITER(hh, smData.map, res, tmp) // iterates the full scene HashMap
    {
        Log(LOG_DEBUG, SM_LOG_PREFIX "Removing %s scene", res->name);
        HASH_DEL(smData.map, res); // removes scene from the scene HashMap
    }

    smData.currentScene = NULL;
    smData.nextScene = NULL;
    smData.isSceneEnded = false;
    return APP_SUCCESS;
}
