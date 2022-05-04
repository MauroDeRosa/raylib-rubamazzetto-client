#include <stdlib.h>

#include "SceneManager.h"
#include <raymath.h>
#include "Scene/SceneSplashScreen.h"
#include "Scene/SceneTitleScreen.h"

#define SPLASH_SCREEN_DURATION_FRAMES (5 * 60.0f)

typedef struct
{
    int timer;
    float rotation;
} SceneSplashScreenData;

void SceneSplashScreenOnInit (void** _data)
{
    *_data = malloc( sizeof(SceneSplashScreenData) );

    // dynamic allocation and modules initial configuration for the current scene here 
    
}

void SceneSplashScreenOnStart (void** _data)
{
    SceneSplashScreenData *data = *_data;

    // variables setup and initial state configuration here 
    data->timer = 0;
    data->rotation = 0;
}

void SceneSplashScreenOnUpdate (void** _data)
{
    SceneSplashScreenData *data = *_data;

    // gets executed every frame, update scene state 
    data->timer++;
    data->rotation++;

    if(data->timer > SPLASH_SCREEN_DURATION_FRAMES)
    {
        SceneManagerSetNext(&SceneTitleScreen);
    }
}

void SceneSplashScreenOnRender (void** _data)
{
    SceneSplashScreenData *data = *_data;
    ClearBackground(LIGHTGRAY);

    Vector2 origin = MeasureTextEx(GetFontDefault(), "SPLASH SCREEN", 30, 5);
    origin = (Vector2){origin.x/2, origin.y/2};
    DrawTextPro(GetFontDefault(), "SPLASH SCREEN", (Vector2){400,300}, origin, data->rotation, 30, 5, YELLOW); 

    // gets executed every frame, draw your privimitives, text and sprites 
    
}

void SceneSplashScreenOnExit (void** _data)
{
    SceneSplashScreenData *data = *_data;

    // free dynamically allocated memory and reset modules configuration to default here 
    
    free(data);
}
