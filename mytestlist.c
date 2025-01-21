/*
Alexei Doell cka067 11345642
Kevin Zhang zbk618 11354912
*/

#include <list.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <list_alloc.h>

int Comparator(void *item, void *comparisonArg) {
    if (*(int*)comparisonArg == *(int*)item) {
        return 1;
    } else {
        return 0;
    }
}
int itemFree(void *item) {
    
    *(int*)item = 0;
    
    return 0;
}


int main(void) {

    LIST* listArr[1000000];
    LIST* list;
    LIST* listTwo;
    LIST* listThree;
    LIST* listFour;
    LIST* listFive;
    LIST* listSix;
    int i, size, test = 100;
    int x = 1, y = 2, z = 20;
    void* test_ptr = (void*)&test;
    InternalList* internal_list;
    InternalNode* internal_node;

    
/* test list creation: successful if no seg fault */
    printf("Testing ListCreate() for six lists (should expand mem)\n");
    list = ListCreate();
    listTwo = ListCreate();
    listThree = ListCreate();
    listFour = ListCreate();
    listFive = ListCreate();
    listSix = ListCreate();

/* phase 2 testing list adders */
    
    printf("Using all list_adders algorithms on empty lists\n");
    printf("Using ListAdd() with node (100) on empty list\n");
    if (ListAdd(list, test_ptr) != 0) {
        printf("ListAdd() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) list);
    if (internal_list->head != internal_list->tail &&
            internal_list->head != internal_list->cursor) {
        printf("ListAdd() did not set the first item inserted as head,"
                " tail, and cursor.\n");
    }

    printf("Using ListInsert() with node (100) on empty list\n");
    if (ListInsert(listTwo, test_ptr) != 0) {
        printf("ListInsert() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) listTwo);
    if (internal_list->head != internal_list->tail &&
            internal_list->head != internal_list->cursor) {
        printf("ListInsert() did not set the first item inserted as head,"
                " tail, and cursor.\n");
    }

    printf("Using ListPrepend() with node (100) on empty list\n");
    if (ListPrepend(listThree, test_ptr) != 0) {
        printf("ListPrepend() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) listThree);
    if (internal_list->head != internal_list->tail &&
            internal_list->head != internal_list->cursor) {
        printf("ListPrepend() did not set the first item inserted as head,"
                " tail, and cursor.\n");
    }

    printf("Using ListApped() with node (100) on empty list\n");
    if (ListAppend(listFour, test_ptr) != 0) {
        printf("ListAppend() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) listFour);
    if (internal_list->head != internal_list->tail &&
            internal_list->head != internal_list->cursor) {
        printf("ListInsert() did not set the first item inserted as head,"
                " tail, and cursor.\n");
    }    

    printf("Testing ListAppend() and ListAdd()\n");

    /* test 3: append/add should update tail when necessary */
    printf("Adding node (100) to end of list\n");
    if (ListAdd(list, test_ptr) != 0) {
        printf("ListAdd() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) list);
    if (internal_list->tail != internal_list->cursor) {
        printf("ListAdd() did not set the new item as the tail\n"); 
    }

    printf("Appending node (100) to end of list\n");
    if (ListAppend(list, test_ptr) != 0) {
        printf("ListAppend() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) list);
    if (internal_list->tail != internal_list->cursor) {
        printf("ListAppend() did not set the new item as the tail\n"); 
    }

    printf("Testing ListPrepend() and ListInsert()...\n");

    /* test 4: insert/prepend should update head when necessary */
    printf("Prepending node (100) to front of list\n");
    if (ListPrepend(list, test_ptr) != 0) {
        printf("ListPrepend() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) list);
    if (internal_list->head != internal_list->cursor) {
        printf("ListPrepend() did not set the new item as the tail\n"); 
    }

    printf("Inserting node (100) to front of list\n");
    if (ListInsert(list, test_ptr) != 0) {
        printf("ListInsert() into an empty list failed.\n");
    }
    internal_list = getListFromTable((unsigned long int) list);
    if (internal_list->head != internal_list->cursor) {
        printf("ListInsert() did not set the new item as the tail\n"); 
    }

    printf("Inserting nodes to test dynamic memory resizing\n");
    /* test 5: adding 10 nodes to a list. if it does not seg fault, it passes */
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);
    ListAdd(list, test_ptr);


    printf("Testing with multiple lists in memory containing nodes\n");

/* test 6: repeat with another list */
    if (ListAdd(listTwo, test_ptr) != 0) {
        printf("ListAdd() into an empty list failed: 2\n");
    }
    internal_list = getListFromTable((unsigned long int) listTwo);
    if (internal_list->tail != internal_list->cursor) {
        printf("ListAdd() did not set the new item as the tail: 2\n"); 
    }

    if (ListAppend(listTwo, test_ptr) != 0) {
        printf("ListAppend() into an empty list failed: 2\n");
    }
    internal_list = getListFromTable((unsigned long int) listTwo);
    if (internal_list->tail != internal_list->cursor) {
        printf("ListAppend() did not set the new item as the tail: 2\n"); 
    }

    if (ListPrepend(listTwo, test_ptr) != 0) {
        printf("ListPrepend() into an empty list failed: 2\n");
    }
    internal_list = getListFromTable((unsigned long int) listTwo);
    if (internal_list->head != internal_list->cursor) {
        printf("ListPrepend() did not set the new item as the tail: 2\n"); 
    }

    if (ListInsert(listTwo, test_ptr) != 0) {
        printf("ListInsert() into an empty list failed: 2\n");
    }
    internal_list = getListFromTable((unsigned long int) listTwo);
    if (internal_list->head != internal_list->cursor) {
        printf("ListInsert() did not set the new item as the tail: 2\n"); 
    }

/* test 7: test ListInsert and ListAdd in between two nodes */
   
    printf("Test ListInsert() and ListAdd() in between two nodes\n");

    /* insert at the beginning to move cursor there */ 
     
    printf("Inserting a node in between the first and second node\n"); 
    ListPrepend(list, test_ptr);    
    ListAdd(list, &x);
    internal_list = getListFromTable((unsigned long int) list);
    internal_node = getNodeFromTable(internal_list->cursor); 

    /* ListPrepend should have moved the cursor to the beginning after inserting
       100. Then ListAdd will have added the new item, x = 1, after 100.
       The list should be {100, 1, 100...} so here we test the next and prev */
    if (*(int*)getNodeFromTable(internal_node->next)->item != 100 &&
            *(int*)getNodeFromTable(internal_node->prev)->item != 100) {
        printf("ListAdd() failed to insert between two nodes.\n");
    }
    
    printf("Inserting a node in between the last and second to last node\n"); 
    /* The cursor will have moved to where 1 is {100, (1), 100...} so if we 
       call ListInsert() with y = 2, the resulting list should be 
       {100, (2), 1, 100...} */
    ListInsert(list, &y);
    internal_node = getNodeFromTable(internal_list->cursor);
    if (*(int*)getNodeFromTable(internal_node->next)->item != 1 &&
            *(int*)getNodeFromTable(internal_node->prev)->item != 100) {
        printf("ListInsert() failed to insert between two nodes.\n");
    }


/* test 8: testing ListCount on empty and non-empty lists */
    printf("Test ListCount on an empty and non-empty list\n");
    if (ListCount(listSix) != 0) {
        printf("ListCount incorrect value\n");
    } 
    if (ListCount(list) != internal_list->size) {
        printf("ListCount incorrect value \n");
    }

/* test 9: ListCurr tests */
    printf("Test ListCurr on an empty and non-empty list\n");
    if (ListCurr(listFive) != NULL) {
        printf("ListCurr returned incorrect value\n");
    }
    if (ListCurr(list) != getNodeFromTable(internal_list->cursor)->item) {
        printf("ListCurr returned incorrect value\n");
    }

/* test 10: ListFirst tests */
    printf("Test ListFirst on an empty and non-empty list\n");
    if (ListFirst(listFive) != NULL) {
        printf("ListFirst returned incorrect value\n");
    }
    if (ListFirst(list) != getNodeFromTable(internal_list->cursor)->item) {
        printf("ListFirst returned incorrect value\n");
    }

/* test 11: ListLast tests */
    printf("Test ListLast on an empty and non-empty list\n");
    if (ListLast(listFive) != NULL) {
        printf("ListLast returned incorrect value\n");
    }
    if (ListLast(list) != getNodeFromTable(internal_list->cursor)->item) {
        printf("ListLast returned incorrect value\n");
    }
   
/* test 12: ListNext tests */
    printf("Test ListNext on an empty and non-empty list"
            ", as well as on a list where curr == tail\n"); 
    if (ListNext(listFive) != NULL) {
        printf("ListNext did not return NULL\n");
    }
    ListFirst(list);
    if (ListNext(list) != getNodeFromTable(internal_list->cursor)->item) {
        printf("ListNext did not return next\n");
    }
    while (ListNext(listTwo) != NULL) {}
    if (ListNext(listTwo) != NULL) {
        printf("Error in ListNext when called at the end of list\n");
    }

/* test 13: ListPrev tests */
    printf("Test ListPrev on an empty list and a non-empty list"
            ", as well as on a list where curr == head\n"); 
    if (ListPrev(listFive) != NULL) {
        printf("ListPrev did not return NULL\n");
    }
    ListNext(list);
    if (ListPrev(list) != getNodeFromTable(internal_list->cursor)->item) {
        printf("ListPrev did not return prev\n");
    }
    while (ListPrev(listThree) != NULL) {}
    if (ListPrev(listThree) != NULL) {
        printf("Error in ListPrev when called at the end of list\n");
    }

/* test 14: ListRemove tests */
    printf("Test ListRemove on empty list, cursor == tail, cursor != tail\n");
    if (ListRemove(listFive) != NULL) {
        printf("ListRemove did not return NULL\n");
    }
    ListLast(list);
    if (ListRemove(list) == NULL) {
        printf("ListRemove when the cursor was on the tail moved to next\n");
    }
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListAdd(list, &x);
    ListFirst(list);
    size = internal_list->size;
    ListRemove(list);
    if (internal_list->size != size - 1) {
        printf("ListRemove did not remove an item\n");
    }

/* test 15: ListTrim tests */
    printf("Test ListTrim on empty list, cursor == tail, cursor != tail\n");
    if (ListTrim(listFive) != NULL) {
        printf("ListTrim did not return NULL\n");
    }
    ListLast(list);
    if (ListTrim(list) == NULL) {
        printf("ListTrim did not return the tail item\n");
    }
    ListFirst(list);
    if (ListTrim(list) == NULL) {
        printf("ListTrim did not return the tail item\n");
    }

/* test 16: ListSearch() tests */
    printf("Testing ListSearch:\n");
    printf("Test ListSearch on an empty list\n");
    if (ListSearch(listFive, Comparator, &z) != NULL) {
        printf("ListSearch on an empty list did not return NULL\n");
    }
    printf("Test ListSearch when cursor is on searched item\n");
    ListAdd(list, &x);
    if (ListSearch(list, Comparator, &x) != &x) {
        printf("ListSearch on cursor did not return cursor item\n");
    }
    printf("Test ListSearch when cursor is before searched item\n");
    ListAppend(list, &z);
    ListFirst(list);
    if (ListSearch(list, Comparator, &z) != &z) {
        printf("ListSearch on full list did not return correct item\n");
    }
    ListLast(list);
    printf("Test ListSearch when cursor is after searched item\n");
    if (ListSearch(list, Comparator, &x) != NULL) {
        printf("ListSearch for item before the cursor failed\n");
    }


/* test 17: ListConcat tests */
    printf("Testing ListConcat:\n");
    printf("Concatenating two valid lists\n");
    ListFree(listFour, itemFree);
    ListFree(listSix, itemFree);

    listFour = ListCreate();
    listSix = ListCreate();

    ListAdd(listFour, &y);
    ListAdd(listFour, &y);
    ListAdd(listFour, &y);
    ListAdd(listSix, &x);
    ListAdd(listSix, &x);
    ListAdd(listSix, &x);

    ListConcat(listFour, listSix);

    if (getListFromTable((unsigned long)listFour)->size != 6) {
        printf("Concatenated list size is wrong\n");
    }
    if (*(int*)ListLast(listFour) != x) {
        printf("Concatenated item is wrong\n");
    }

/* test 18: ListFree tests */
    printf("Testing ListFree:\n");
    printf("Test ListFree on an empty list\n");
    ListFree(listFive, itemFree);
    if (getListFromTable((unsigned long)listFive)->in_use) {
        printf("Freed list still exists\n");
    }
    printf("Test ListFree on a non-empty list\n");
    ListFree(list, itemFree);
    if (getListFromTable((unsigned long)list)->in_use) {
        printf("Freed list still exists\n");
    }
    printf("Creating new list and nodes using freed memory\n");
    list = ListCreate();
    ListAdd(list, &x);
    if (*(int*)ListCurr(list) != x) {
        printf("Error creating new list and nodes from freed list\n");
    }

/* test 19 stress tests */
    printf("Inserting 5 nodes into 1000000 lists each\n");
    for (i = 0; i < 1000000; i++) {
        listArr[i] = ListCreate();
    }
    for (i = 0; i < 1000000; i++) {
        ListAdd(listArr[i], &x);
        ListAdd(listArr[i], &x);
        ListAdd(listArr[i], &x);
        ListAdd(listArr[i], &x);
        ListAdd(listArr[i], &x);
    }
    printf("Freeing all lists and nodes\n");
    for (i = 0; i < 1000000; i++) {
        ListFree(listArr[i], itemFree);
    }
    ListFree(list, itemFree);
    ListFree(listTwo, itemFree);
    ListFree(listThree, itemFree);
    ListFree(listFour, itemFree);

    list = ListCreate();
    ListFree(list, itemFree);


    
    printf("ALL TESTS COMPLETED\n");
    return 0;
}
