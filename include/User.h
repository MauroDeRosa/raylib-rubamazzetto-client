#ifndef __USER_H__
#define __USER_H__

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>
#include <external/uthash/uthash.h>

#define USERS_FILE_PATH "users.dat"
#define USER_USERNAME_MAX_LEN 40
#define USER_PASSWORD_MAX_LEN 40

typedef struct
{
    char username[USER_USERNAME_MAX_LEN + 1];
    char password[USER_PASSWORD_MAX_LEN + 1];
    UT_hash_handle hh;
} User_t;

extern User_t *users;
extern size_t usersCount;

int UsersInit();
bool UsersLoad(const char *path);
bool UsersWrite(const char *path);
size_t UsersCount();

User_t *UserRegister(char *username, char *password);
bool UserUpdate(User_t *user, char *password);
bool UserDelete(User_t *user);
User_t *UserLogin(char *username, char *password);

bool UserUsernameCheckLength(char* username);
bool UserPasswordCheckLength(char* password);

User_t *UserFind(char *username);

#endif /* __USER_H__ */
