#include "Scene/NewScene.h" 

struct NewSceneData
{
    // insert your scene variables here
    int example;
}; struct NewSceneData _NewSceneData;
void NewSceneStart()
{
    struct NewSceneData* $ = &_NewSceneData;
    
}

void NewSceneUpdate()
{
    struct NewSceneData* $ = &_NewSceneData;
    
}

void NewSceneFixedUpdate()
{
    struct NewSceneData* $ = &_NewSceneData;
    
}

void NewSceneRender()
{
    struct NewSceneData* $ = &_NewSceneData;
    DrawText("dio gatto", 100, 100, 50, GREEN);   
}

void NewSceneExit()
{
    struct NewSceneData* $ = &_NewSceneData;
    
}
