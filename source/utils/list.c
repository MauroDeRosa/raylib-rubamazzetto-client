#include <stdio.h>
#include <stdlib.h>
#include "utils/list.h"

void ListInit(List *list, freeCallback freeCbk)
{
    list->head = NULL;
    list->count = 0;
    list->freeCbk = freeCbk;
}

void ListPushFront(List *list, void *item)
{
    if (item == NULL)
    {
        fprintf(stderr, "Item is not valid.");
        exit(EXIT_FAILURE);
    }

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    
    newNode->item = item;
    newNode->next = list->head;
    list->head = newNode;

    list->count++;
}

void ListPushBack(List *list, void *item)
{
    ListNode *current = list->head;
    
    if (item == NULL)
    {
        fprintf(stderr, "Item is not valid.");
        exit(EXIT_FAILURE);
    }

    if (current == NULL)
    {
        ListPushFront(list, item);
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = NULL;
        current->next = newNode;

        list->count++;
    }
}

void *ListPopFront(List *list)
{
    ListNode *oldHead = list->head;

    if (oldHead == NULL)
    {
        fprintf(stderr, "List is empty.");
        exit(EXIT_FAILURE);
    }

    void *item = oldHead->item;

    list->head = oldHead->next;
    free(oldHead);
    list->count--;
    return item;
}

void *ListPopBack(List *list)
{
    ListNode *current = list->head;
    ListNode *prev = list->head;

    void *item;
    
    if (current == NULL)
    {
        fprintf(stderr, "List is empty.");
        exit(EXIT_FAILURE);
    }

    while (current->next != NULL)
    {
        prev = current;
        current = current->next;
    }
    
    item = current->item;
    free(current);
    prev->next = NULL;
    list->count--;
    return item;
}

void *ListDeleteAt(List *list, uint16_t index, bool mustFree)
{
    ListNode *prev = list->head;
    void *item;

    if (prev == NULL)
    {
        fprintf(stderr, "List is empty.");
        exit(EXIT_FAILURE);
    }
    else if (index == 0)
    {
        item = prev->item; 
        list->head = list->head->next;
        
        if (mustFree)
        {
            list->freeCbk(item);
            prev->item = NULL;
        }

        free(prev);
        list->count--;
        
        return mustFree ? NULL : item;
    }

    for (uint16_t i = 1; i < index; i++)
    {
        if (prev->next == NULL)
        {
            fprintf(stderr, "Index out of bounds.");
            exit(EXIT_FAILURE);
        }

        prev = prev->next;
    }

    ListNode *toDelete = prev->next;
    item = toDelete->item;
    prev->next = toDelete->next;

    if (mustFree)
    {
        list->freeCbk(item);
        toDelete->item = NULL;
    }

    free(toDelete);
    list->count--;

    return mustFree ? NULL : item;
}

void *ListGetAt(List *list, uint16_t index)
{
    ListNode *current = list->head;
    void *item;

    if (current == NULL)
    {
        fprintf(stderr, "List is empty.");
        exit(EXIT_FAILURE);
    }

    for (uint16_t i = 0; i < index; i++)
    {
        if (current->next == NULL)
        {
            fprintf(stderr, "Index out of bounds.");
            exit(EXIT_FAILURE);
        }

        current = current->next;
    }
    
    return item = current->item;
}

void ListInsertAt(List *list, uint16_t index, void *item)
{
    if (item == NULL)
    {
        fprintf(stderr, "Item is not valid.");
        exit(EXIT_FAILURE);
    }

    ListNode *current = list->head;
    ListNode *prev = list->head;

    if (current == NULL)
    {
        fprintf(stderr, "List is empty.");
        exit(EXIT_FAILURE);
    }

    for (uint16_t i = 0; i < index; i++)
    {
        if (current->next == NULL)
        {
            fprintf(stderr, "Index out of bounds.");
            exit(EXIT_FAILURE);
        }
        prev = current;
        current = current->next;
    }

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->item = item;

    if (index == 0)
    {
        newNode->next = list->head;
        list->head = newNode;
    }
    else
    {
        prev->next = newNode;
        newNode->next = current;
    }

    list->count++;
}


ListIterator *ListIteratorInit(List *list, uint16_t index)
{
    if (list == NULL || list->head == NULL)
    {
        fprintf(stderr, "List is empty.");
        exit(EXIT_FAILURE);
    }

    if (index >= list->count)
    {
        fprintf(stderr, "Index out of bounds.");
        exit(EXIT_FAILURE);
    }

    ListIterator *iterator = (ListIterator *)malloc(sizeof(ListIterator));

    iterator->current = list->head;
    iterator->isStarted = false;

    for (uint16_t i = 0; i < index; i++)
    {
        iterator->current = iterator->current->next;
    }
    
    return iterator;
}

void *ListIteratorNext(ListIterator *listIterator)
{
    if (listIterator->isStarted && listIterator->current != NULL)
    {
        listIterator->current = listIterator->current->next;
    }
    else
    {
        listIterator->isStarted = true;
    }

    if (listIterator->current == NULL)
    {
        return NULL;
    }
    else
    {
        return listIterator->current->item;
    }
}