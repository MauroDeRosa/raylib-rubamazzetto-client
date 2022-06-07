#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdint.h>

typedef void (*freeCallback)(void*);

typedef struct ListNode_t
{
    void *item;
    struct ListNode_t *next;
}ListNode;

typedef struct
{
    ListNode *head;
    uint16_t count;
    freeCallback freeCbk;
}List;

typedef struct 
{
    ListNode *current;
    bool isStarted;
}ListIterator;


void ListInit(List *list, freeCallback freeCbk);

void ListPushFront(List *list, void *);

void ListPushBack(List *list, void *);

void *ListPopFront(List *list);

void *ListPopBack(List *list);

void *ListDeleteAt(List *list, uint16_t index, bool mustFree);

void *ListGetAt(List *list, uint16_t index);

void ListInsertAt(List *list, uint16_t index, void *);

ListIterator *ListIteratorInit(List *list, uint16_t index);

void *ListIteratorNext(ListIterator *listIterator);

#endif // __LIST_H__