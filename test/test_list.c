#include <assert.h>
#include <string.h>
#include "utils/list.h"
#include "utils/logger.h"

#define LIST_LOG_PREFIX LOG_COLOR_YELLOW "[TestList] " LOG_COLOR_RESET

int main(int argc, char const *argv[])
{
    struct listNode_t *list = NULL;
    struct listNode_t *emptyList = NULL;
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
    assert(strcmp(str_test4, list->item));

    assert(listPopFront(&emptyList) == NULL);

    char *str_test5 = calloc(1000, sizeof(char));

    strcpy(str_test5, "sjdfsldkfjsifdojiajspiodsaspodkapksmcaisjdpaoisdpaoskdpoaskdkcmspoifjdsoifjsdofijsdkmvclxzkmvoxlcivjosidjfposidf");
    listPushBack(&emptyList, str_test5);
    char *str_tmp = listPopFront(&emptyList);
    assert(str_tmp != NULL);
    free(str_tmp);
    assert(str_test5 == NULL); // TODO: Fix not being able to free the memory
    return 0;
}