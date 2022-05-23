#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "utils/list.h"
#include "utils/logger.h"

#define LIST_LOG_PREFIX LOG_COLOR_YELLOW "[TestList] " LOG_COLOR_RESET

int main(int argc, char const *argv[])
{
    
    struct listNode_t *list = NULL;
    struct listNode_t *emptyList = NULL;
    
    /*listPushFront(&list, NULL);
    listInsertByIndex(&list, 5, NULL);

    listPushFront(&list, "TestFront");
    char *strFront1 = listGetByIndex(&list, 0);
    assert(strcmp(strFront1, (char *)listGetByIndex(&list, 0)) == 0);

    listPushBack(&list, "TestBack");
    char *strBack1 = listGetByIndex(&list, 1);
    assert(strcmp(strBack1, (char *)listGetByIndex(&list, 1)) == 0);

    listPushFront(&list, "TestFront2");
    char *strFront2 = listGetByIndex(&list, 0);
    assert(strcmp(strFront2, strFront1) != 0);

    //Log(LOG_INFO, LIST_LOG_PREFIX "%s : %s", strFront2, (char *)listGetByIndex(&list, 0));
    char *strFront3 = listPopFront(&list);
    assert(strcmp(strFront2, strFront3) == 0);

    char *strBack2 = listPopBack(&list);
    assert(strcmp(strBack1, strBack2) == 0);

    listDeleteByIndex(&emptyList, 1);*/

    listPushFront(&emptyList, "TEST");
    listInsertByIndex(&emptyList, 1, "TEST 2");
    listInsertByIndex(&emptyList, 2, "TEST 3");
    listPushFront(&emptyList, "TEST 4");
    Log(LOG_INFO, LIST_LOG_PREFIX "%s", (char *)listGetByIndex(&emptyList, 1));

    return 0;
}