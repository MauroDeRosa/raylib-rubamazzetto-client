#include "game/User.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Config.h"
#include "utils/logger.h"
#include "utils/stringutils.h"

#define USERS_LOG_PREFIX LOG_COLOR_YELLOW "[Users] " LOG_COLOR_RESET

User_t *users;
size_t usersCount = 0;

bool UserUsernameCheckLength(char *username)
{
    size_t len = strlen(username);
    if (len > USER_USERNAME_MAX_LEN)
    {
        Log(LOG_WARNING, USERS_LOG_PREFIX "Username %s is %zu long, maximum accepted length is %zu", username, len, USER_USERNAME_MAX_LEN);
        return false;
    }

    return true;
}

bool UserPasswordCheckLength(char *password)
{
    size_t len = strlen(password);
    if (len > USER_PASSWORD_MAX_LEN)
    {
        Log(LOG_WARNING, USERS_LOG_PREFIX "Password %s is %zu long, maximum accepted length is %zu", password, len, USER_USERNAME_MAX_LEN);
        return false;
    }

    return true;
}

size_t UsersCount()
{
    return usersCount;
}

bool UsersLoad(const char *path)
{
    FILE *file = fopen(path, "rb");
    
    if(file == NULL)
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX, "Unable to open '%s' in read binary mode", path);
        return false;
    }

    User_t *tmpUser = malloc(sizeof(User_t));

    while (!feof(file))
    {
        fread(tmpUser, sizeof(User_t), 1, file);
        if(tmpUser)
        {
            Log(LOG_DEBUG, USERS_LOG_PREFIX "loaded user '%s':'%s'", tmpUser->username, tmpUser->password);
            UserRegister(tmpUser->username, tmpUser->password);
        }
    }

    free(tmpUser);
    fclose(file);
    return true;
}

bool UsersWrite(const char *path)
{
    FILE *file = fopen(path, "wb");
    
    if(file == NULL)
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX, "Unable to open '%s' in write binary mode", path);
        return false;
    }

    User_t *currentUser, *tmp;
    HASH_ITER(hh, users, currentUser, tmp)
    {
        fwrite(currentUser, sizeof(User_t), 1, file);
    }

    fclose(file);
    return true;
}

User_t *UserRegister(char *username, char *password)
{
    if ( (UserUsernameCheckLength(username) || UserPasswordCheckLength(password)) == false )
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX "invalid length username or password");
        return NULL;
    }

    User_t *user = UserFind(username);

    if(user != NULL)
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX "Unable to register new user: user '%s' yet exists");
        return NULL;
    }

    user = calloc(1, sizeof(User_t));
    strcpy(user->username, username);
    strcpy(user->password, password);
    usersCount++;
    HASH_ADD_STR(users, username, user);
}

bool UserUpdate(User_t *user, char *password)
{
    if (UserPasswordCheckLength(password) == false)
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX "invalid length password");
        return APP_ERROR;
    }
    if (user == NULL)
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX "Can't update user NULL pointer received! %s%s", __FILE__, __LINE__);
        return APP_ERROR;
    }

    strcpy(user->password, password);

    return true ;
}

bool UserDelete(User_t *user)
{
    if (user == NULL)
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX "Can't delete user NULL pointer received! %s%s", __FILE__, __LINE__);
        return APP_ERROR;
    }

    HASH_DEL(users, user);
    free(user);
    usersCount--;
    return true;
}

User_t *UserLogin(char *username, char *password)
{
    if ( (UserUsernameCheckLength(username) || UserPasswordCheckLength(password)) == false )
    {
        Log(LOG_ERROR, USERS_LOG_PREFIX "invalid length username or password");
        return NULL;
    }

    User_t *user = UserFind(username);

    if (user == NULL)
    {
        Log(LOG_WARNING, USERS_LOG_PREFIX "Username %s doesn't exist!", username);
        return NULL;
    }

    if (strcmp(user->password, password) != 0)
    {
        Log(LOG_WARNING, USERS_LOG_PREFIX "Wrong password");
        return NULL;
    }

    return user;
}

User_t *UserFind(char *username)
{
    User_t *user;
    HASH_FIND_STR(users, username, user);
    return user;
}