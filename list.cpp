#include "list.h"


inline void ListConnectNodes(List* list, const size_t first_phys_id, const size_t second_phys_id) {
    assert(list);

    list->elems[first_phys_id].next_phys_id = second_phys_id;
    list->elems[second_phys_id].prev_phys_id = first_phys_id;
}


inline void ListConnectArray(List* list, const size_t begin_phys_id, const size_t end_phys_id) {
    assert(list);

    list->elems[begin_phys_id].cur_phys_id = begin_phys_id;
    for (size_t phys_id = begin_phys_id + 1; phys_id <= end_phys_id; phys_id++) {
        list->elems[phys_id].cur_phys_id = phys_id;
        ListConnectNodes(list, phys_id - 1, phys_id);
    }
}


int ListAlloc(List* list) {
    assert(list);

    list->elems = (ListNode*)calloc(LIST_DEFAULT_CAPACITY, sizeof(ListNode));
    if (!list->elems)
        return LIST_ALLOC_ERROR;

    list->elems[0].prev_phys_id = LIST_INVALID_ID;
    ListConnectArray(list, 0, list->capacity - 1);
    list->elems[list->capacity - 1].next_phys_id = LIST_INVALID_ID;

    list->n_elems      = LIST_DEFAULT_N_ELEMS;
    list->capacity     = LIST_DEFAULT_CAPACITY;
    list->head_phys_id = LIST_INVALID_ID;
    list->tail_phys_id = LIST_INVALID_ID;
    list->free_phys_id = 0;
}


int ListCheckAndUpdateCapacity(List* list) {
    assert(list);

    if (list->n_elems == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        ListNode* new_elems = (ListNode*)realloc(list->elems, sizeof(ListNode) * new_capacity);
        if (!new_elems)
            return LIST_ALLOC_ERROR;
        list->free_phys_id = list->n_elems;
        ListConnectArray(list, list->n_elems, new_capacity - 1);
    } else
        return LIST_NO_ERRORS;
}


int ListPushFront(List* list, const ListElemT new_elem) {
    assert(list);

    int check_res = 0;
    if ((check_res = ListCheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = list->elems[list->free_phys_id].next_phys_id;
    ListConnectNodes(list, list->head_phys_id, list->free_phys_id);
    list->head_phys_id = list->free_phys_id;
    list->free_phys_id = new_free_phys_id;
    list->elems[list->head_phys_id].prev_phys_id = LIST_INVALID_ID;
    list->elems[list->head_phys_id].data = new_elem;

    return LIST_NO_ERRORS;
}


int ListPushBack(List* list, const ListElemT new_elem) {
    assert(list);

    int check_res = 0;
    if ((check_res = ListCheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = list->elems[list->free_phys_id].next_phys_id;
    ListConnectNodes(list, list->free_phys_id, list->head_phys_id);
    list->head_phys_id = list->free_phys_id;
    list->free_phys_id = new_free_phys_id;
    list->elems[list->head_phys_id].prev_phys_id = LIST_INVALID_ID;
    list->elems[list->tail_phys_id].data = new_elem;
    ++list->n_elems;

    return LIST_NO_ERRORS;
}


int ListGetByLogicId(List* list, size_t logic_id, ListElemT* found) {
    assert(list);
    assert(found);

    if (logic_id >= list->n_elems)
        return LIST_ABSENCE_OF_REQUIRED_ELEM;

    while (logic_id > 0) {
        
    }
}


void ListDestruct(List* list) {
    assert(list);

    free(list->elems);
    *list = {};
}
