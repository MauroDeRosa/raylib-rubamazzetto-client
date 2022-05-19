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
    struct listNode_t *listDeleteTest = NULL;
    assert(list == NULL);

    char *str_test1 = "test";
    listPushFront(&list, str_test1);
    assert(list->item != NULL);
    assert(strcmp((char *)list->item, str_test1) == 0);

    char *str_test2 = "test 2";
    listPushFront(&list, str_test2);
    assert(list->next != NULL);
    assert(list->next->item != NULL);
    assert(strcmp((char *)list->item, str_test2) == 0);

    char *str_test3 = "test 3";
    listPushBack(&list, str_test3);
    assert(list->next->next != NULL);
    assert(list->next->next->item != NULL);
    assert(strcmp((char *)list->next->next->item, str_test3) == 0);

    char *str_test4 = listPopFront(&list);
    Log(LOG_INFO, LIST_LOG_PREFIX "%s : %s", str_test4, (char *)list->item);

    assert(listPopFront(&emptyList) == NULL);

    char *str_test5 = calloc(1000, sizeof(char));

    strcpy(str_test5, "sjdfsldkfjsifdojiajspivjosidjfposidf");
    listPushBack(&emptyList, str_test5);
    char *str_tmp = listPopFront(&emptyList);
    assert(str_tmp != NULL);
    free(str_tmp);
    //assert(str_test5 == NULL); // TODO: Fix not being able to free the memory

    char *str_test6 = listPopBack(emptyList);

    char *str_test7 = calloc(200, sizeof(char));

    strcpy(str_test7, "PopBack Test");
    listPushBack(&list, str_test7);
    char *str_test8 = listPopBack(list);
    Log(LOG_INFO, LIST_LOG_PREFIX "%s : %s", str_test8, str_test7);
    assert(strcmp(str_test8, str_test7) == 0);

    char *strTest = "terza posizione";
    listPushFront(&listDeleteTest, strTest);
    char *strTest2 = "seconda posizione";
    listPushFront(&listDeleteTest, strTest2);
    char *strTest3 = "prima posizione";
    listPushFront(&listDeleteTest, strTest3);

    listDeleteByIndex(&listDeleteTest, 1);

    char *str = listGetByIndex(&listDeleteTest, 0);
    Log(LOG_INFO, LIST_LOG_PREFIX "%s", str);

    return 0;
}