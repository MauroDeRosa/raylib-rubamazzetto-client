#include "SceneManager.h"
#include "Scene/SceneSplashScreen.h"
#include "Scene/SceneLoadScreen.h"

#include <raylib.h>
#include <raymath.h>
#include "raylib-extra/raygui.h"

#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    int example;
} SceneSplashScreenData;

// dynamic allocation and modules initial configuration for the current scene here
void SceneSplashScreenOnInit (void** _$)
{
    *_$ = malloc( sizeof(SceneSplashScreenData) );
    
}

// variables setup and initial state configuration here
void SceneSplashScreenOnStart (void** _$)
{
    SceneSplashScreenData *$ = *_$;
    
}

// gets executed every frame, update scene state
void SceneSplashScreenOnUpdate (void** _$)
{
    SceneSplashScreenData *$ = *_$;
    
}

// gets executed every SCENE_MANAGER_FIXEDUPDATE_STEP, update scene state
void SceneSplashScreenOnFixedUpdate (void** _$)
{
    SceneSplashScreenData *$ = *_$;
    
}

// gets executed every frame, draw your privimitives, text and sprites
void SceneSplashScreenOnRender (void** _$)
{
    SceneSplashScreenData *$ = *_$;
    ClearBackground(RAYWHITE);
    
}

// free dynamically allocated memory and reset modules configuration to default here
void SceneSplashScreenOnExit (void** _$)
{
    SceneSplashScreenData *$ = *_$;
    
    free($);
}
