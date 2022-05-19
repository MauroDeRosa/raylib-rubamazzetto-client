#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

struct listNode_t
{
    void *item;
    size_t itemCount;
    struct listNode_t *next;
};

/**
 * @brief
 *
 * @param head
 */
void listPushFront(struct listNode_t **head, void *);

/**
 * @brief
 *
 * @param head
 */
void listPushBack(struct listNode_t **head, void *);

/**
 * @brief
 *
 * @param head
 * @return void* memory allocation is let to be freed by the user
 */
void *listPopFront(struct listNode_t **head);

/**
 * @brief
 *
 * @param head
 * @return void* memory allocation is let to be freed by the user
 */
void *listPopBack(struct listNode_t *head);

/**
 * @brief
 *
 * @param head
 * @param index
 * @return void* memory allocation is let to be freed by the user
 */
void *listDeleteByIndex(struct listNode_t **head, size_t index);

/**
 * @brief
 *
 * @param head
 * @param index
 * @return item at the specified index
 */
void *listGetByIndex(struct listNode_t **head, size_t index);

/**
 * @brief 
 * 
 * @param head 
 * @param index 
 * @return void* 
 */
void *listInsertByIndex(struct listNode_t **head, size_t index, void *);

/**
 * @brief 
 * 
 * @param head 
 * @param index 
 * @return void* 
 */
void *listIterateTo(struct listNode_t *head, size_t index);
#endif /* __LIST_H__ */