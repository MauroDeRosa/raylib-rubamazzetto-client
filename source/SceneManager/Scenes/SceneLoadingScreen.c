#include "SceneManager/Scenes/SceneLoadingScreen.h"
#include <raylib.h>
#include <raymath.h>
#include "external/raygui.h"
#include "external/easings.h"
#include "gui/gui.h"
#include "utils/logger.h"

#include <pthread.h>   // POSIX style threads management
#include <stdatomic.h> // C11 atomic data types
#include <time.h>      // Required for: clock()

// Using C11 atomics for synchronization. A plain bool (or any plain data type for that matter) can't be used for inter-thread synchronization
static atomic_bool dataLoaded = ATOMIC_VAR_INIT(false); // Data Loaded completion indicator
static int dataProgress = 0; // Data progress accumulator
static void *LoadDataThread(void *arg);

static void *LoadDataThread(void *arg)
{
    rmLoad();
    atomic_store(&dataLoaded, true);

    return NULL;
}

struct SceneLoadingScreenData
{
    // insert your scene variables here
    pthread_t threadId; // Loading data thread id

    enum
    {
        STATE_WAITING,
        STATE_LOADING,
        STATE_FINISHED
    } state;
    int framesCounter;
};
struct SceneLoadingScreenData *_SceneLoadingScreenData;

void SceneLoadingScreenStart()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData = calloc(1, sizeof(struct SceneLoadingScreenData));
    // memory and variables initialization here
    $->state = STATE_WAITING;
    $->framesCounter = 0;
}

void SceneLoadingScreenUpdate()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // update scene, called every frame
    switch ($->state)
    {
    case STATE_WAITING:
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            int error = pthread_create(&$->threadId, NULL, &LoadDataThread, NULL);
            if (error != 0)
                Log(LOG_ERROR, "Error creating loading thread");
            else
                Log(LOG_INFO, "Loading thread initialized successfully");

            $->state = STATE_LOADING;
        }
    }
    break;
    case STATE_LOADING:
    {
        $->framesCounter++;
        if (atomic_load(&dataLoaded))
        {
            $->framesCounter = 0;
            $->state = STATE_FINISHED;
        }
    }
    break;
    case STATE_FINISHED:
    {
        smNext("END");
    }
    break;
    }
}

void SceneLoadingScreenFixedUpdate()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // update scene, called every fixed timestep
}

void SceneLoadingScreenRender()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // render scene, draw your art here <3

    switch ($->state)
    {
    case STATE_WAITING:
        DrawText("PRESS ENTER to START LOADING DATA", 150, 170, 20, DARKGRAY);
        break;
    case STATE_LOADING:
    {
        // draw progress bar
        if (($->framesCounter / 15) % 2)
            DrawText("LOADING...", SCREEN_WIDTH/2 - (40*9)/2, SCREEN_HEIGHT/2 - 20, 40, DARKBLUE);
    }
    break;
    default:
        break;
    }

    DrawRectangleLines(150, 200, 500, 60, DARKGRAY);
}

void SceneLoadingScreenExit()
{
    struct SceneLoadingScreenData *$ = _SceneLoadingScreenData;
    // TODO: clean memory here pls :3
    free(_SceneLoadingScreenData);
}
