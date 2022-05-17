#include <assert.h>
#include <string.h>
#include "utils/list.h"
#include "utils/logger.h"

#define LIST_LOG_PREFIX LOG_COLOR_YELLOW "[TestList] " LOG_COLOR_RESET

int main(int argc, char const *argv[])
{
    struct listNode_t *list = NULL;
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

    return 0;
}
