#ifndef __UI_LOGIN_H__
#define __UI_LOGIN_H__

#include <stdbool.h>
#include "game/User.h"

struct uiLoginBox_t
{
    Vector2 position;
    Vector2 center;
    Vector2 corner;

    Vector2 size;
    float borderSize;
    
    Rectangle boxRect;
    Rectangle buttonRect;
    Rectangle usernameRect;
    Rectangle passwordRect;

    Color backgroundColor;
    Color foregroundColor;
    Color borderColor;

    User_t *user;
    char username[40];
    char password[40];

    bool isLoginPressed;
    bool isUsernameSelected;
    bool isPasswordSelected;
    bool isLoggedIn;
    bool isLoginFailed;

    double startTime;
    double endTime;
};

struct uiLoginBox_t* UiLoginBoxCreate(Vector2 position);
struct uiLoginBox_t* UiLoginBoxCreateEx(Vector2 position, Color backgroundColor, Color foregroundColor, Color borderColor, float borderSize);

void uiUpdateLoginBox(struct uiLoginBox_t* lbox);
void uiRenderLoginBox(struct uiLoginBox_t* loginBox);

void UiLoginBoxFree(struct uiLoginBox_t *loginBox);

#endif /* __UI_LOGIN_H__ */
