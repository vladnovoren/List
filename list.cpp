#include "list.h"


static void ListConnectNodes(List* list, const size_t first_id, const size_t second_id) {
    assert(list);

    list->elems[first_id].next_id = second_id;
    list->elems[second_id].prev_id = first_id;
}


static void ListConnectArray(List* list, const size_t begin_id, const size_t end_id) {
    assert(list);

    list->elems[begin_id].cur_id = begin_id;
    for (size_t id = begin_id + 1; id <= end_id; id++) {
        list->elems[id].cur_id = id;
        ListConnectNodes(list, id - 1, id);
    }
}


int ListAlloc(List* list) {
    assert(list);

    list->elems = (ListNode*)calloc(LIST_DEFAULT_CAPACITY, sizeof(ListNode));
    if (!list->elems)
        return LIST_ALLOC_ERROR;

    list->elems[0].prev_id = LIST_INVALID_ID;
    ListConnectArray(list, 0, list->capacity - 1);
    list->elems[list->capacity - 1].next_id = LIST_INVALID_ID;

    list->n_elems  = LIST_DEFAULT_N_ELEMS;
    list->capacity = LIST_DEFAULT_CAPACITY;
}


int ListCheckAndUpdateCapacity(List* list) {
    assert(list);

    if (list->n_elems == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        ListNode* new_elems = (ListNode*)realloc(list->elems, sizeof(ListNode) * new_capacity);
        if (!new_elems)
            return LIST_ALLOC_ERROR;
        list->free_id = list->n_elems;
        ListConnectArray(list, list->n_elems, new_capacity - 1);
    } else
        return LIST_NO_ERRORS;
}


int ListPushFront(List* list, const ListElemT new_elem) {
    assert(list);

    int check_res = 0;
    if ((check_res = ListCheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_id = list->elems[list->free_id].next_id;
    ListConnectNodes(list, list->head_id, list->free_id);
    list->head_id = list->free_id;
    list->free_id = new_free_id;
    list->elems[list->head_id].prev_id = LIST_INVALID_ID;
    list->elems[list->head_id].data = new_elem;

    return LIST_NO_ERRORS;
}


int ListPushBack(List* list, const ListElemT new_elem) {
    assert(list);

    int check_res = 0;
    if ((check_res = ListCheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_id = list->elems[list->free_id].next_id;
    ListConnectNodes(list, list->free_id, list->head_id);
    list->head_id = list->free_id;
    list->free_id = new_free_id;
    list->elems[list->head_id].prev_id = LIST_INVALID_ID;
    list->elems[list->tail_id].data = new_elem;

    return LIST_NO_ERRORS;
}


void ListDestruct(List* list) {
    assert(list);

    free(list->elems);
    *list = {};
}
