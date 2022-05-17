#include "utils/list.h"
#include "utils/logger.h"

void listPushFront(struct listNode_t **head, void *item)
{
    struct listNode_t *listNode;
    listNode = (struct listNode_t *)malloc(sizeof(struct listNode_t));

    listNode->item = item;
    listNode->next = *head;
    *head = listNode;
}

void listPushBack(struct listNode_t *head, void *item)
{
    struct listNode_t *listNodeCurrent;
    listNodeCurrent = head;

    // set current node to the tail by cycling through the list
    while (listNodeCurrent->next != NULL)
    {
        listNodeCurrent = listNodeCurrent->next;
    }

    listNodeCurrent->next = (struct listNode_t *)malloc(sizeof(struct listNode_t));
    listNodeCurrent->next->item = item;
    listNodeCurrent->next->next = NULL;
}