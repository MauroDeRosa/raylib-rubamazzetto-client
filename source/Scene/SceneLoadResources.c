#include <stdlib.h>
#include "SceneManager.h"
#include "Scene/SceneLoadResources.h"

typedef struct
{
    int example;
} SceneLoadResourcesData;

void SceneLoadResourcesOnInit (void** _data)
{
    *_data = malloc( sizeof(SceneLoadResourcesData) );

    // dynamic allocation and modules initial configuration for the current scene here 
    
}

void SceneLoadResourcesOnStart (void** _data)
{
    SceneLoadResourcesData *data = *_data;

    // variables setup and initial state configuration here 
    
}

void SceneLoadResourcesOnUpdate (void** _data)
{
    SceneLoadResourcesData *data = *_data;

    // gets executed every frame, update scene state 
    
}

void SceneLoadResourcesOnRender (void** _data)
{
    SceneLoadResourcesData *data = *_data;
    ClearBackground(RAYWHITE);

    // gets executed every frame, draw your privimitives, text and sprites 
    
}

void SceneLoadResourcesOnExit (void** _data)
{
    SceneLoadResourcesData *data = *_data;

    // free dynamically allocated memory and reset modules configuration to default here 
    
    free(data);
}
