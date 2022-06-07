#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <inttypes.h>
#include "utils/list.h"

List *list;
List *listIterator;
uint16_t *array;

int init_SuiteList(void);
int clean_SuiteList(void);
void test_ListPushFront(void);
void test_ListPushBack(void);
void test_ListPopFront(void);
void test_ListPopBack(void);
void test_ListDeleteAt(void);
void test_ListGetAt(void);
void test_ListInsertAt(void);

int init_SuiteIterator(void);
int clean_SuiteIterator(void);
void test_ListIteratorIndex0(void);
void test_ListIteratorIndex50(void);
void test_ListIteratorEnd(void);

void stringFree(void *item)
{
    char *ptr = item;
    free(ptr);
}

int main(int argc, char const *argv[])
{
    CU_pSuite SuiteList = NULL;
    CU_pSuite SuiteIterator = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    SuiteList = CU_add_suite("SuiteList", init_SuiteList, clean_SuiteList);
    if (SuiteList == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(SuiteList, "test ListPushFront", test_ListPushFront) == NULL) ||
        (CU_add_test(SuiteList, "test ListPushBack", test_ListPushBack) == NULL) ||
        (CU_add_test(SuiteList, "test ListPopFront", test_ListPopFront) == NULL) ||
        (CU_add_test(SuiteList, "test ListPopBack", test_ListPopBack) == NULL) ||
        (CU_add_test(SuiteList, "test ListDeleteAt", test_ListDeleteAt) == NULL) ||
        (CU_add_test(SuiteList, "test ListGetAt", test_ListGetAt) == NULL) ||
        (CU_add_test(SuiteList, "test ListInsertAt", test_ListInsertAt) == NULL)) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    SuiteIterator = CU_add_suite("SuiteIterator", init_SuiteIterator, clean_SuiteIterator);
    if (SuiteIterator == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(SuiteIterator, "test ListIteratorIndex0", test_ListIteratorIndex0) == NULL) ||
        (CU_add_test(SuiteIterator, "test ListIteratorIndex50", test_ListIteratorIndex50) == NULL) ||
        (CU_add_test(SuiteIterator, "test ListIteratorEnd", test_ListIteratorEnd) == NULL)) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

    return 0;
}

int init_SuiteList(void)
{
    list = (List *)malloc(sizeof(List));
    ListInit(list, stringFree);
    return 0;
}

int clean_SuiteList(void)
{
    free(list);
    return 0;
}

int init_SuiteIterator(void)
{
    listIterator = (List *)malloc(sizeof(List));
    ListInit(listIterator, stringFree);

    array = calloc(100, sizeof(uint16_t));

    for(uint16_t i = 0; i < 100; i++)
    {
        array[i] = i;
        ListPushBack(listIterator, &array[i]);
    }

    return 0;
}

int clean_SuiteIterator(void)
{
    free(listIterator);
    free(array);
    return 0;
}

void test_ListPushFront(void)
{
    ListPushFront(list, "TEST_FRONT");
    ListPushFront(list, "ANOTHER_FRONT");
    ListPushFront(list, "YET_ANOTHER_FRONT");
    CU_ASSERT(list->head != NULL)
    CU_ASSERT(strcmp(list->head->item, "YET_ANOTHER_FRONT") == 0);
    CU_ASSERT(list->count == 3);
}

void test_ListPushBack(void)
{
    ListPushBack(list, "TEST_BACK");
    ListPushBack(list, "ANOTHER_BACK");
    ListPushBack(list, "YET_ANOTHER_BACK");
    CU_ASSERT(list->head != NULL)
    
    ListNode *current = list->head;
    uint16_t count = 1;

    while(current->next != NULL)
    {
        current = current->next;
        count++;
    }

    CU_ASSERT(strcmp(current->item, "YET_ANOTHER_BACK") == 0);
    CU_ASSERT(list->count == count); 
}

void test_ListPopFront(void)
{   
    ListNode *oldHead = list->head;
    char *string = ListPopFront(list);
    CU_ASSERT(list->head != oldHead);
    CU_ASSERT(list->count == 5);
    CU_ASSERT(strcmp(string, "YET_ANOTHER_FRONT") == 0);
}

void test_ListPopBack(void)
{
    ListNode *oldTail = list->head;

    while (oldTail->next != NULL)
    {
        oldTail = oldTail->next;
    }

    char *string = ListPopBack(list);

    ListNode *newTail = list->head;

    while (newTail->next != NULL)
    {
        newTail = newTail->next;
    }
    
    CU_ASSERT(oldTail != newTail);
    CU_ASSERT(list->count == 4);
    CU_ASSERT(strcmp(string, "YET_ANOTHER_BACK") == 0);
}

void test_ListDeleteAt(void)
{
    char *string1 = ListDeleteAt(list, 0, false);
    char *string2 = ListDeleteAt(list, 1, false);
    CU_ASSERT(list->count == 2);
    CU_ASSERT(strcmp(string1, "ANOTHER_FRONT") == 0);
    CU_ASSERT(strcmp(string2, "TEST_BACK") == 0);

    char *string3 = malloc(sizeof(char) * 100);
    strcpy(string3, "freeCbk_TEST");
    ListPushFront(list, string3);

    ListNode *oldHead = list->head;

    ListDeleteAt(list, 0, true);

    CU_ASSERT(oldHead != list->head);

    char *string4 = malloc(sizeof(char) * 100);
    strcpy(string4, "freeCbk_TEST");
    ListPushBack(list, string4);

    ListNode *oldTail = list->head;

    while (oldTail->next != NULL)
    {
        oldTail = oldTail->next;
    }

    ListDeleteAt(list, list->count - 1, true);

    ListNode *newTail = list->head;

    while (newTail->next != NULL)
    {
        newTail = newTail->next;
    }
    
    CU_ASSERT(oldTail != newTail);
}

void test_ListGetAt(void)
{
    char *string1 = ListGetAt(list, 0);
    char *string2 = ListGetAt(list, 1);
    CU_ASSERT(strcmp(string1, "TEST_FRONT") == 0);
    CU_ASSERT(strcmp(string2, "ANOTHER_BACK") == 0);
}

void test_ListInsertAt(void)
{
    ListInsertAt(list, 0, "TEST_INSERT");
    char *string1 = ListGetAt(list, 0);

    ListInsertAt(list, 1, "ANOTHER_INSERT");
    char *string2 = ListGetAt(list, 1);

    ListInsertAt(list, list->count - 1, "BACK_INSERT");
    char *string3 = ListGetAt(list, list->count - 2);

    CU_ASSERT(strcmp(string1, "TEST_INSERT") == 0);
    CU_ASSERT(strcmp(string2, "ANOTHER_INSERT") == 0);
    CU_ASSERT(strcmp(string3, "BACK_INSERT") == 0);
}

void test_ListIteratorIndex0(void)
{
    ListIterator *iterator = ListIteratorInit(listIterator, 0);

    for (uint16_t i = 0; true; i++)
    {
        uint16_t *n = ListIteratorNext(iterator);

        if (n == NULL)
        {
            break;
        }
        else
        {
            CU_ASSERT(array[i] == *n);
        }
    }

    free(iterator);
}

void test_ListIteratorIndex50(void)
{
    ListIterator *iterator = ListIteratorInit(listIterator, 50);

    for (uint16_t i = 50; true; i++)
    {
        uint16_t *n = ListIteratorNext(iterator);

        if (n == NULL)
        {
            break;
        }
        else
        {
            CU_ASSERT(array[i] == *n);
        }
    }

    free(iterator);
}

void test_ListIteratorEnd(void)
{
    ListIterator *iterator = ListIteratorInit(listIterator, 99);
    ListIteratorNext(iterator);
    
    CU_ASSERT(ListIteratorNext(iterator) == NULL);

    free(iterator);
}