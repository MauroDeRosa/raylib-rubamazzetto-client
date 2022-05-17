#include <raylib.h>
#include "external/raygui.h"
#include <raymath.h>

#include "utils/logger.h"
#include "gui/gui.h"
#include "game/User.h"

#define LOGIN_BOX_HEIGHT (350.0f)
#define LOGIN_BOX_WIDTH (300.0f)

struct uiLoginBox_t *uiLoginBoxCreate(Vector2 position)
{
    return uiLoginBoxCreateEx(position, BLACK, WHITE, GRAY, 1.0f);
}

struct uiLoginBox_t *uiLoginBoxCreateEx(Vector2 position, Color backgroundColor, Color foregroundColor, Color borderColor, float borderSize)
{
    struct uiLoginBox_t *lbox = calloc(1, sizeof(struct uiLoginBox_t));

    lbox->position = position;
    lbox->size = (Vector2){LOGIN_BOX_WIDTH, LOGIN_BOX_HEIGHT};
    lbox->corner = Vector2Add(lbox->position, lbox->size);
    lbox->center = Vector2Add(lbox->position, Vector2Scale(lbox->size, 0.5f));
    lbox->borderSize = borderSize;
    lbox->backgroundColor = backgroundColor;
    lbox->foregroundColor = foregroundColor;
    lbox->borderColor = borderColor;

    lbox->boxRect = (Rectangle){
        .x = lbox->position.x,
        .y = lbox->position.y,
        .width = lbox->size.x,
        .height = lbox->size.y};

    lbox->usernameRect = (Rectangle){
        .x = lbox->position.x + 10.0f,
        .y = lbox->position.y + 50.0f,
        .width = lbox->size.x - 20.0f,
        .height = 40.0f};

    lbox->passwordRect = (Rectangle){
        .x = lbox->position.x + 10.0f,
        .y = lbox->position.y + 160.0f,
        .width = lbox->size.x - 20.0f,
        .height = 40.0f};

    lbox->buttonRect = (Rectangle){
        .x = lbox->position.x + 10.0f,
        .y = lbox->corner.y - 100.0f,
        .width = lbox->size.x - 20.0f,
        .height = 90.0f},

    lbox->isLoginPressed = false;

    return lbox;
}

void uiUpdateLoginBox(struct uiLoginBox_t *lbox)
{
    if (lbox->isLoggedIn)
    {
        return;
    }

    if (lbox->isLoginFailed)
    {
        if (GetTime() - lbox->startTime >= 1.5f)
        {
            lbox->isLoginFailed = false;
        }
    }
    else
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            lbox->isUsernameSelected = CheckCollisionPointRec(mousePosition, lbox->usernameRect);
            lbox->isPasswordSelected = CheckCollisionPointRec(mousePosition, lbox->passwordRect);
        }
        if ((lbox->isUsernameSelected || lbox->isPasswordSelected) && IsKeyPressed(KEY_TAB))
        {
            lbox->isUsernameSelected = !lbox->isUsernameSelected;
            lbox->isPasswordSelected = !lbox->isPasswordSelected;
        }
        if (lbox->isLoginPressed || (IsKeyPressed(KEY_ENTER) && (lbox->isPasswordSelected || lbox->isUsernameSelected)))
        {
            lbox->user = UserLogin(lbox->username, lbox->password);
            if (lbox->user != NULL)
            {
                lbox->isLoggedIn = true;
            }
            else
            {
                lbox->startTime = GetTime();
                lbox->isLoginFailed = true;
                lbox->password[0] = '\0';
            }
        }
    }
}

void uiRenderLoginBox(struct uiLoginBox_t *lbox)
{
    DrawRectangle(lbox->boxRect.x, lbox->boxRect.y, lbox->boxRect.width, lbox->boxRect.height, lbox->backgroundColor);

    if (lbox->borderSize > 0.0f)
        DrawRectangleLinesEx(lbox->boxRect, lbox->borderSize, lbox->borderColor);

    if (lbox->isLoggedIn)
    {
        DrawText("Welcome", lbox->center.x - MeasureText("Welcome", 40) / 2, lbox->center.y - 25, 40, GREEN);
        DrawText(lbox->username, lbox->center.x - MeasureText(lbox->username, 30) / 2, lbox->center.y + 25, 30, GREEN);
    }
    else
    {
        if (lbox->isLoginFailed)
        {
            DrawText("LOGIN FAILED", lbox->center.x - MeasureText("LOGIN FAILED", 30.0f) / 2, lbox->center.y - 15.0f, 30.0f, RED);
        }
        else
        {
            DrawText("Username", lbox->position.x + 10.0f, lbox->position.y + 10.0f, 30.0f, lbox->foregroundColor);
            GuiTextBox(lbox->usernameRect, lbox->username, 40, lbox->isUsernameSelected);
            DrawText("Password", lbox->position.x + 10.0f, lbox->position.y + 120.0f, 30.0f, lbox->foregroundColor);
            GuiTextBox(lbox->passwordRect, lbox->password, 40, lbox->isPasswordSelected);
            lbox->isLoginPressed = GuiButton(lbox->buttonRect, "LOGIN");
        }
    }
}

void uiLoginBoxFree(struct uiLoginBox_t *lbox)
{
    free(lbox);
}
