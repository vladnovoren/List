#include "list.h"


inline void ListConnectNodes(List* list, const size_t first_phys_id, const size_t second_phys_id) {
    assert(list);

    list->elems[first_phys_id].next_phys_id = second_phys_id;
    list->elems[second_phys_id].prev_phys_id = first_phys_id;
}


inline void ListConnectArray(List* list, const size_t begin_phys_id, const size_t end_phys_id) {
    assert(list);

    list->elems[begin_phys_id].prev_phys_id = LIST_INVALID_ID;
    list->elems[begin_phys_id].cur_phys_id = begin_phys_id;
    for (size_t phys_id = begin_phys_id + 1; phys_id <= end_phys_id; phys_id++) {
        list->elems[phys_id].cur_phys_id = phys_id;
        ListConnectNodes(list, phys_id - 1, phys_id);
    }
    list->elems[end_phys_id].next_phys_id = LIST_INVALID_ID;
}


int ListAlloc(List* list) {
    assert(list);

    list->elems = (ListNode*)calloc(LIST_DEFAULT_CAPACITY, sizeof(ListNode));
    if (!list->elems)
        return LIST_ALLOC_ERROR;

    list->n_elems  = LIST_DEFAULT_N_ELEMS;
    list->capacity = LIST_DEFAULT_CAPACITY;
    ListConnectArray(list, 0, list->capacity - 1);
    list->used_head_phys_id = LIST_INVALID_ID;
    list->used_tail_phys_id = LIST_INVALID_ID;
    list->free_head_phys_id = 0;
    list->free_tail_phys_id = list->capacity - 1;

    return LIST_NO_ERRORS;
}


int ListCheckAndUpdateCapacity(List* list) {
    assert(list);

    if (list->n_elems == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        ListNode* new_elems = (ListNode*)realloc(list->elems, sizeof(ListNode) * new_capacity);
        if (!new_elems)
            return LIST_ALLOC_ERROR;
        list->elems = new_elems;
        list->capacity = new_capacity;
        list->free_head_phys_id = list->n_elems;
        list->free_tail_phys_id = list->capacity - 1;
        ListConnectArray(list, list->n_elems, list->capacity - 1);
    }

    return LIST_NO_ERRORS;
}


int ListPushFront(List* list, const ListElemT new_elem, size_t* phys_id) {
    assert(list);

    int check_res = 0;
    if ((check_res = ListCheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = list->elems[list->free_head_phys_id].next_phys_id;
    if (list->n_elems)
        ListConnectNodes(list, list->free_head_phys_id, list->used_head_phys_id);
    else {
        list->elems[list->free_head_phys_id].next_phys_id = LIST_INVALID_ID;
        list->elems[list->free_head_phys_id].prev_phys_id = LIST_INVALID_ID;
        list->used_tail_phys_id = list->free_head_phys_id;
    }
    list->used_head_phys_id = list->free_head_phys_id;
    list->elems[list->used_head_phys_id].data = new_elem;
    list->free_head_phys_id = new_free_phys_id;
    if (new_free_phys_id != LIST_INVALID_ID)
        list->elems[new_free_phys_id].prev_phys_id = LIST_INVALID_ID;
    else
        list->free_tail_phys_id = LIST_INVALID_ID;
    ++list->n_elems;

    return LIST_NO_ERRORS;
}


int ListPushBack(List* list, const ListElemT new_elem, size_t* phys_id) {
    assert(list);

    int check_res = 0;
    if ((check_res = ListCheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = list->elems[list->free_head_phys_id].next_phys_id;
    if (list->n_elems)
        ListConnectNodes(list, list->used_tail_phys_id, list->free_head_phys_id);
    else {
        list->elems[list->free_head_phys_id].next_phys_id = LIST_INVALID_ID;
        list->elems[list->free_head_phys_id].prev_phys_id = LIST_INVALID_ID;
        list->used_head_phys_id = list->free_head_phys_id;
    }
    list->used_tail_phys_id = list->free_head_phys_id;
    list->elems[list->used_tail_phys_id].data = new_elem;
    list->free_head_phys_id = new_free_phys_id;
    if (new_free_phys_id != LIST_INVALID_ID)
        list->elems[new_free_phys_id].prev_phys_id = LIST_INVALID_ID;
    else
        list->free_tail_phys_id = LIST_INVALID_ID;
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

    return LIST_NO_ERRORS;
}


void ListDestruct(List* list) {
    assert(list);

    free(list->elems);
    *list = {};
}
