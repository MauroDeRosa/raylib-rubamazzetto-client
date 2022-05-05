#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene/SceneSplashScreen.h"
//#include "Scene/SceneLoadScreen.h"

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
    ResourceManager.Init();
}

// variables setup and initial state configuration here
void SceneSplashScreenOnStart (void** _$)
{
    SceneSplashScreenData *$ = *_$;
    ResourceManager.AddResource(RESOURCE_IMAGE, "myImage", "./Images/myImage.png");
    ResourceManager.AddResource(RESOURCE_TEXTURE, "myTexture", "./Textures/myTexture.png");
    ResourceManager.AddResource(RESOURCE_SOUND, "mySound", "./Sounds/mySound.mp3");
    ResourceManager.AddResource(RESOURCE_SOUND, "mySound", "./Sounds/mySoundFixed.mp3");
    ResourceManager.RemoveResource(RESOURCE_TEXTURE, "myTexture");
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
    
    if(SceneManagerGetTime() > 2.0f)
    {
        SceneManagerSetState(SCENEMGR_CLOSE);
    }
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
    ResourceManager.Destroy();
    free($);
}
