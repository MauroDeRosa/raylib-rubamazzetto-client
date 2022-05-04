#include "SceneManager.h"
#include "logger.h"

bool SceneManagerInit(Scene *startScene, Scene *quitScene)
{
    Log(LOG_INFO, "[SceneManager] initializing Scene Manager...", NULL);
    if (startScene == NULL || quitScene == NULL)
    {
        Log(LOG_ERROR, "[SceneManager] startScene and quitScene can't be NULL");
        return false;
    }
    _sceneManagerQuit = quitScene;
    SceneManagerTransition(startScene);

    return true;
}

void SceneManagerLoop(bool quitSignal)
{
    while (!quitSignal)
    {
        _sceneManagerCurrent->onUpdate(0);
        _sceneManagerCurrent->onRender(0);
    }

    //TODO: implement quit scene
    
}

void SceneManagerTransition(Scene *nextScene)
{
    Scene *nextScene = NULL;
    if (_sceneManagerCurrent != NULL)
    {
        nextScene = _sceneManagerCurrent->onExit(0).nextScene;
        if (!nextScene)
        {
            Log(LOG_ERROR, "[SceneManager] %s->onExit().nextScene is not defined, moving to %s", _sceneManagerCurrent->name, _sceneManagerQuit->name);
            nextScene = _sceneManagerQuit;
        }
    }

    _sceneManagerCurrent = nextScene;
    Log(LOG_INFO, "[SceneManager] Initializing %s...", _sceneManagerCurrent->name);
    
    if(nextScene->onInit(0).status == SCENECBST_FALIURE){
        Log(LOG_ERROR, "[SceneManager] Initialization faliure for %s! moving to %s", _sceneManagerCurrent->name, _sceneManagerQuit->name);
        _sceneManagerCurrent = _sceneManagerQuit;
    }

    if(nextScene->onStart(0).status == SCENECBST_FALIURE){
        Log(LOG_ERROR, "[SceneManager] Startup faliure for %s! moving to %s", _sceneManagerCurrent->name, _sceneManagerQuit->name);
        _sceneManagerCurrent = _sceneManagerQuit;
    }
}

void SceneManagerClose()
{
    Log(LOG_INFO, "[SceneManager] closing Scene Manager...", NULL);

    //TODO: implement close routine
}
