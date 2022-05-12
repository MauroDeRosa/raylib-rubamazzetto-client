#include <assert.h>
#include <stdio.h>
#include "utils/logger.h"
#include "game/User.h"
#include <unistd.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "Config.h"
#include <string.h>
#include <stdbool.h>
#include "utils/stringutils.h"

#define TEST_FILE "test_user.dat"
#define TEST_PREFIX LOG_COLOR_MAGENTA "[test_user] " LOG_COLOR_RESET

int main(int argc, char const *argv[])
{
    if (access(TEST_FILE, F_OK))
    {
        remove(TEST_FILE);
    }

    Log(LOG_INFO, TEST_PREFIX "Trying loading users from non existing file %s", TEST_FILE);
    assert(UsersLoad(TEST_FILE) == false);

    Log(LOG_INFO, TEST_PREFIX "Trying writing empty users to file %s", TEST_FILE);
    assert(UsersWrite(TEST_FILE) == true);

    char username[6][100] =
        {
            "Joseph",
            "Gianni",
            "Mock",
            "davidgayhasololusernameelapasswordlunghiilcazzonientepropriomispiaceperlui",
            "butitsusernamesucks",
            "thisuserwillfailsecurelycauseitsusernameislongerthanroccosiffredisdick",
        };
    char password[6][100] =
        {
            "Joestar",
            "Morandi",
            "ASort",
            "davidgayhasololusernameelapasswordlunghiilcazzonientepropriomispiaceperlui",
            "thisuserwillfailsecurelycauseitspasswordislongerthanroccosiffredisdick",
            "butitspasswordsucks",
        };
    size_t count = 0;

    for (size_t i = 0; i < 6; i++)
    {
        if (UserRegister(username[i], password[i]) != NULL)
        {
            count++;
        }
        else
        {
            Log(LOG_WARNING, TEST_PREFIX "user '%s' '%s' failed", username[i], password[i]);
        }
    }

    Log(LOG_INFO, TEST_PREFIX "trying delete '%s' '%s')", username[0], password[0]);
    User_t *tmpUser = UserFind(username[0]);
    if (tmpUser != NULL)
    {
        assert(UserDelete(tmpUser) == true); // user deleted
        count--;
    }
    assert(tmpUser == NULL || strcmp(tmpUser->username, username[0]) != 0); // user deleted succesfully

    Log(LOG_INFO, TEST_PREFIX "Checking if user count corresponds to created users (test_counter: %zu, UserCount(): %zu)", count, UsersCount());
    assert(UsersCount() == count);

    Log(LOG_INFO, TEST_PREFIX "registering user: 'admin' 'admin'");
    assert(UserRegister("admin", "admin") != NULL);

    Log(LOG_INFO, TEST_PREFIX "login user: 'admin' 'adm1n' expected login failure");
    assert(UserLogin("admin", "adm1n") == NULL);

    Log(LOG_INFO, TEST_PREFIX "login user: 'admin' 'admin' expected successful login");
    assert(UserLogin("admin", "admin") != NULL);

    Log(LOG_INFO, TEST_PREFIX "update user: 'admin' 'caciocavallo' and login with new password");

    assert(UserLogin("admin", "admin") != NULL);
    tmpUser = UserFind("admin");
    if (tmpUser != NULL)
    {
        assert( UserUpdate(tmpUser, "caciocavallo") == true); // user updated
    }
    assert(UserLogin("admin", "admin") == NULL);
    assert(UserLogin("admin", "caciocavallo") != NULL);


    Log(LOG_INFO, TEST_PREFIX "test terminated...");

    return 0;
}
