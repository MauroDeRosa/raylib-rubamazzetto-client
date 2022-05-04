#include "SceneManager.h"
#include "logger.h"

#ifdef LOG_STYLE_USE_COLOR
#define SCENE_MANAGER_PREFIX "\033[33m[SceneManager]\033[0m "
#else
#define SCENE_MANAGER_PREFIX "[SceneManager] "
#endif // LOG_STYLE_USE_COLOR

const char *_SceneManagerStateString[] = {"FALIURE\0", "SUCCESS\0", "NEXT\0", "CLOSE\0"};
DefineScene(SceneManagerInitialization, "SceneManagerInitialization", NULL, NULL, NULL, NULL, NULL, NULL);

bool SceneManagerInit(Scene *startScene)
{
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Initializing Scene Manager...", NULL);
    SceneManager.fixedUpdateTimer = 0;
    SceneManager.sceneInitTime = 0;

    if (startScene == NULL)
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "startScene can't be NULL");
        SceneManager.current = NULL;
        SceneManager.next = NULL;
        SceneManager.status = SCENEMGR_FALIURE;
        SceneManager.running = false;
        return false;
    }
    else
    {
        SceneManager.current = &SceneManagerInitialization;
        SceneManager.running = true;
        SceneManagerSetNext(startScene);
        _SceneManagerNext();
        SceneManager.fixedUpdateTimer = 0;
        return true;
    }
}

void _SceneManagerSceneInit()
{
    SceneManager.sceneInitTime = GetTime();
    SceneManagerSetState(SCENEMGR_SUCCESS);
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Initializing %s...", SceneManager.current->name);
    SceneManager.current->onInit(&SceneManager.current->data);
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Starting %s...", SceneManager.current->name);
    SceneManager.current->onStart(&SceneManager.current->data);
}

void SceneManagerLoop()
{

    while (!WindowShouldClose() && SceneManager.running)
    {
        if (SceneManager.status == SCENEMGR_FALIURE || SceneManager.status == SCENEMGR_CLOSE)
        {
            if (SceneManager.status == SCENEMGR_FALIURE)
            {
                Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Scene %s returned a FALIURE state, starting close procedure...", SceneManager.current->name);
                SceneManagerSetState(SCENEMGR_CLOSE);
            }
            break;
        }
        else if (SceneManager.status == SCENEMGR_NEXT)
        {
            _SceneManagerNext();
            continue;
        }

        SceneManager.current->onUpdate(&SceneManager.current->data);
        
        if (SceneManager.fixedUpdateTimer >= SCENE_MANAGER_FIXEDUPDATE_STEP)
        {
            SceneManager.fixedUpdateTimer = 0;
            SceneManager.current->onFixedUpdate(&SceneManager.current->data);
        }
        
        BeginDrawing();
        SceneManager.current->onRender(&SceneManager.current->data);
        EndDrawing();

        SceneManager.fixedUpdateTimer += GetFrameTime();
    }

    _SceneManagerClose();
}

void _SceneManagerNext()
{
    if (SceneManager.next == NULL)
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Next scene can't be NULL");
        SceneManagerSetState(SCENEMGR_CLOSE);
    }

    if (SceneManager.current == NULL | SceneManager.current == &SceneManagerInitialization)
    {
        SceneManager.current = SceneManager.next;
        SceneManager.next = NULL;
        _SceneManagerSceneInit();
    }
    else
    {
        SceneManager.current->onExit(&SceneManager.current->data);
        SceneManager.current = SceneManager.next;
        SceneManager.next = NULL;
        _SceneManagerSceneInit();
    }
}

void _SceneManagerClose()
{
    if (SceneManager.current != NULL)
    {
        Log(LOG_INFO, SCENE_MANAGER_PREFIX "Calling Exit function for %s...", SceneManager.current->name);
        SceneManager.current->onExit(&SceneManager.current->data);
    }
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Closing Scene Manager...", NULL);
    SceneManager.running = false;
    SceneManager.current = NULL;
    SceneManager.next = NULL;
    SceneManager.status = SCENEMGR_CLOSE;
}

void SceneManagerSetState(SceneManagerState status)
{
    SceneManager.status = status;
    Log(LOG_INFO, SCENE_MANAGER_PREFIX "Scene %s state set to %s", SceneManager.current != NULL ? SceneManager.current->name : "NULL", _SceneManagerStateString[status]);
}

void SceneManagerSetNext(Scene *nextScene)
{
    if (nextScene == NULL)
    {
        Log(LOG_ERROR, SCENE_MANAGER_PREFIX "Next scene can't be set to NULL");
        SceneManagerSetState(SCENEMGR_FALIURE);
    }
    else
    {
        Log(LOG_INFO, SCENE_MANAGER_PREFIX "Setting next scene from %s to %s", SceneManager.current != NULL ? SceneManager.current->name : "NULL", nextScene->name);
        SceneManager.next = nextScene;
        SceneManagerSetState(SCENEMGR_NEXT);
    }
}

double SceneManagerGetTime()
{
    return GetTime() - SceneManager.sceneInitTime;
}