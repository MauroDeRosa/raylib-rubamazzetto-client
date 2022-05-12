#include "external/easings.h"
#include <time.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    time_t t = time(NULL);
    
    time_t now = time(0);
    int startTime = localtime(&now)->tm_sec;
    int currentTime = startTime;

    int duration = 10;
    float startPositionX = 0.0f;
    float finalPositionX = 30.0f;
    float currentPositionX = startPositionX;
 
    while (currentPositionX < finalPositionX)
    {
        currentPositionX = EaseSineIn(currentTime, startPositionX, finalPositionX - startPositionX, startTime+duration);
        now = time(0);
        currentTime = localtime(&now)->tm_sec;
        printf("%f\n", currentPositionX);
    }
    return 0;
}
