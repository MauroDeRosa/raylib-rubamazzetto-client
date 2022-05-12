#include "SceneManager/Scenes/SceneSplashScreen.h"
#include "external/easings.h"
#include <raymath.h>
#include "gui/gui.h"
struct SceneSplashScreenData
{
    // insert your scene variables here
    int state;
    bool centerOrigin;
    Card mycards[40];
    float startRotation;
    float rotation;
    Vector2 startPosition[40];
    Vector2 position[40];
    double state1_begin_time;
};
struct SceneSplashScreenData _SceneSplashScreenData;
void SceneSplashScreenStart()
{
    struct SceneSplashScreenData *$ = &_SceneSplashScreenData;
    CardsInit();
    for (size_t i = 0; i < 40; i++)
    {
        $->mycards[i] = cards[i];
    }
    $->state = 0;
}

void SceneSplashScreenUpdate()
{
    struct SceneSplashScreenData *$ = &_SceneSplashScreenData;
    if (SceneManager.Time() < 3.0f && $->state == 0)
    {
        $->startRotation = sin(SceneManager.Time() * 3) * 22.5f;
    }
    else if (SceneManager.Time() >= 3.0f && $->state == 0)
    {
        $->state = 1;
        $->rotation = 1;
        for (size_t i = 0; i < 40; i++)
        {
            $->position[i] = $->startPosition[i];
        }
        
        $->state1_begin_time = SceneManager.Time();
    }
}

void SceneSplashScreenFixedUpdate()
{
    struct SceneSplashScreenData *$ = &_SceneSplashScreenData;

    if ($->state == 0)
    {
        Card tmp;
        size_t idx1 = (size_t)(SceneManager.Time() * 1000) % 40;
        size_t idx2 = (size_t)(SceneManager.Time() * 2000) % 40;
        tmp = $->mycards[idx1];
        $->mycards[idx1] = $->mycards[idx2];
        $->mycards[idx2] = tmp;
    }
}

void SceneSplashScreenRender()
{
    struct SceneSplashScreenData *$ = &_SceneSplashScreenData;

    for (int i = 0; i < 40; i++)
    {
        if ($->state == 0)
        {
            float scale = .25f;
            float cws = CARD_WIDTH * scale;
            float chs = CARD_HEIGHT * scale;

            $->startPosition[i] = (Vector2){
                .x = (cws * 1.50f) + (cws / 2) * (i % 10) + (int)(cws * (i % 10)),
                .y = (chs * 0.60f) + (chs / 2) * (i / 10) + (int)(chs * (i / 10)), 
            };
            DrawCard($->mycards[i], $->startPosition[i], $->startRotation, scale, true, true);
        }
        else if ($->state == 1)
        {
            float scale = .25f;
            float cws = CARD_WIDTH * scale;
            float chs = CARD_HEIGHT * scale;
            Vector2 goal = (Vector2){
                .x=10 + cws/2 + 1,
                .y=SCREEN_HEIGHT/2 - chs/2
            };

            Vector2 distance = (Vector2){
                .x=fabs($->startPosition[i].x - goal.x),
                .y=fabs($->startPosition[i].y - goal.y)
            };

            float time = SceneManager.Time() - $->state1_begin_time;
            float error = 1.0f;

            if ($->rotation > 0)
            {
                $->rotation = $->startRotation - EaseSineInOut(time, 0.0f, fabs($->startRotation), 1.0f);
            }
            if($->position[i].x > goal.x)
            {
                $->position[i].x = $->startPosition[i].x - EaseSineInOut(time, 0.0f, distance.x, 2.0f);
            }
            if($->position[i].y <= goal.y - error || $->position[i].y >= goal.y + error)
            {
                if($->position[i].y >= goal.y + error)
                {
                    $->position[i].y = $->startPosition[i].y - EaseSineInOut(time, 0.0f, distance.y, 2.0f);
                }
                else if($->position[i].y <= goal.y - error)
                {
                    $->position[i].y = $->startPosition[i].y + EaseSineInOut(time, 0.0f, distance.y, 2.0f);
                }
            }

            DrawCard($->mycards[i], $->position[i], $->rotation, scale, true, true);
        }
    }
}

void SceneSplashScreenExit()
{
    struct SceneSplashScreenData *$ = &_SceneSplashScreenData;
}
