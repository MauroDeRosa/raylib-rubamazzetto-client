#include "SceneManager/Scenes/SceneProfileLogin.h"
#include <raylib.h>
#include <raymath.h>
#include "external/raygui.h"
#include "external/easings.h"
#include "utils/logger.h"
#include "gui/gui.h"

#define AFTER_TITLE_POSITION 200
#define TEXT_USERNAME_POSITION (Vector2){ScreenCenter.x, AFTER_TITLE_POSITION}
#define TEXTBOX_USERNAME_POSITION (Vector2){ScreenCenter.x, AFTER_TITLE_POSITION + TEXT_SIZE + 10}
#define TEXT_PASSWORD_POSITION (Vector2){ScreenCenter.x, AFTER_TITLE_POSITION + TEXT_SIZE + TEXTBOX_SIZE.y + 10*4}
#define TEXTBOX_PASSWORD_POSITION (Vector2){ScreenCenter.x, AFTER_TITLE_POSITION + TEXT_SIZE*2 + TEXTBOX_SIZE.y + 10*5}

#define TEXT_SIZE 40
#define TEXTBOX_SIZE (Vector2){300, 50}

struct SceneProfileLoginData
{
    double timer;

    struct uiTextbox_t *usernameBox;
    struct uiTextbox_t *passwordBox;

    bool isLoginFailed;
    bool isLoginPressed;
    bool isRegisterPressed;
};
struct SceneProfileLoginData *_SceneProfileLoginData;

void SceneProfileLoginStart()
{
    struct SceneProfileLoginData *$ = _SceneProfileLoginData = calloc(1, sizeof(struct SceneProfileLoginData));
    $->usernameBox = uiTextboxCreate(TEXTBOX_USERNAME_POSITION, TEXTBOX_SIZE, UI_HALIGN_CENTER, UI_VALIGN_TOP, 40, NULL);
    $->passwordBox = uiTextboxCreate(TEXTBOX_PASSWORD_POSITION, TEXTBOX_SIZE, UI_HALIGN_CENTER, UI_VALIGN_TOP, 40, NULL);

    $->usernameBox->next = $->passwordBox;
    $->passwordBox->next = $->usernameBox;
}

void SceneProfileLoginUpdate()
{
    struct SceneProfileLoginData *$ = _SceneProfileLoginData;
    uiTextboxUpdate($->usernameBox);
    Log(LOG_INFO, "tab: %s\n", IsKeyPressed(KEY_TAB) ? "true" : "false");
    uiTextboxUpdate($->passwordBox);
}

void SceneProfileLoginFixedUpdate()
{
    struct SceneProfileLoginData *$ = _SceneProfileLoginData;
}

void SceneProfileLoginRender()
{
    struct SceneProfileLoginData *$ = _SceneProfileLoginData;
    uiCarpetRender();

    uiTextDraw("LOGIN or REGISTER PROFILE", (Vector2){ScreenCenter.x, 25}, UI_HALIGN_CENTER, UI_VALIGN_TOP, 80, RED, true);
    uiTextDraw("Username", TEXT_USERNAME_POSITION, UI_HALIGN_CENTER, UI_VALIGN_TOP, 40, WHITE, false);
    uiTextboxRender($->usernameBox);
    uiTextDraw("Password", TEXT_PASSWORD_POSITION, UI_HALIGN_CENTER, UI_VALIGN_TOP, 40, WHITE, false);
    uiTextboxRender($->passwordBox);

    $->isLoginPressed = GuiButton(
        (Rectangle){
            .x = ScreenCenter.x - 100,
            .y = ScreenSize.y - 120 ,
            .width = 200,
            .height = 50,
        },
        "Login");

    $->isLoginPressed = GuiButton(
        (Rectangle){
            .x = ScreenCenter.x - 100,
            .y = ScreenSize.y - 60,
            .width = 200,
            .height = 50,
        },
        "Register");
}

void SceneProfileLoginExit()
{
    struct SceneProfileLoginData *$ = _SceneProfileLoginData;
    // TODO: clean memory here pls :3

    uiTextboxFree($->usernameBox);
    uiTextboxFree($->passwordBox);
    free(_SceneProfileLoginData);
}
