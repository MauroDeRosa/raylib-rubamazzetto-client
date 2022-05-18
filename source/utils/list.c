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

void listPushBack(struct listNode_t **head, void *item)
{
    struct listNode_t *listNodeCurrent;
    listNodeCurrent = *head;

    // if list is empty 
    if (*head == NULL)
    {
        *head = (struct listNode_t *)malloc(sizeof(struct listNode_t));
        (*head)->item = item;
        (*head)->next = NULL;
    }
    else
    {
        // set current node to the tail by cycling through the list
        while (listNodeCurrent->next != NULL)
        {
            listNodeCurrent = listNodeCurrent->next;
        }

        listNodeCurrent->next = (struct listNode_t *)malloc(sizeof(struct listNode_t));
        listNodeCurrent->next->item = item;
        listNodeCurrent->next->next = NULL;
    }
}

void *listPopFront(struct listNode_t **head)
{
    struct listNode_t *listNode = NULL;
    void *item;

    if (*head == NULL)
    {
        Log(LOG_ERROR, LOG_COLOR_RED "[List] " LOG_COLOR_RESET "List is empty", NULL);
        return NULL;
    }

    listNode = (*head)->next;
    item = (*head)->item;
    free(*head);
    *head = listNode;

    return item;
}

void *listPopBack(struct listNode_t *head)
{
    struct listNode_t *listNodeCurrent = head;
    void *item;

    //checks if list is empty or else if there's only one item in the list and removes it
    if (head == NULL)
    {
        Log(LOG_ERROR, LOG_COLOR_RED "[List] " LOG_COLOR_RESET "List is empty", NULL);
        return NULL;
    }
    else if (head->next == NULL)
    {
        item = head->item;
        free(head);
        return item;
    }

    //set current on the second last position
    while (listNodeCurrent->next->next != NULL)
    {
        listNodeCurrent = listNodeCurrent->next;
    }

    item = listNodeCurrent->next->item;
    free(listNodeCurrent->next);
    
    return item;
}

void *listDeleteByIndex(struct listNode_t **head, size_t index)
{
    struct listNode_t *listNodeCurrent = *head;
    struct listNode_t *listNodeTemp = NULL;

    if (index == 0)
    {
        listPopFront(head); //fix
    }

    //iterates to the node before the node to delete
    for (size_t i = 0; i < index - 1; i++)
    {   
        if (listNodeCurrent->next == NULL)
        {
            Log(LOG_ERROR, LOG_COLOR_RED "[List] " LOG_COLOR_RESET "Index error, out of bounds", NULL);
            return NULL;
        }

        listNodeCurrent = listNodeCurrent->next;
    }

    listNodeTemp = listNodeCurrent->next;
    listNodeCurrent->next = listNodeTemp->next;

    free(listNodeTemp);
}

void *listGetByIndex(struct listNode_t **head, size_t index)
{
    struct listNode_t *listNodeCurrent = *head;
    void *item;

    if (index == 0)
    {
        item = (*head)->item;
        return item;
    }

    for (size_t i = 0; i < index - 1; i++)
    {   
        if (listNodeCurrent->next == NULL)
        {
            Log(LOG_ERROR, LOG_COLOR_RED "[List] " LOG_COLOR_RESET "Index error, out of bounds", NULL);
            return NULL;
        }

        listNodeCurrent = listNodeCurrent->next;
    }

    item = listNodeCurrent->item;
    
    return item;
}