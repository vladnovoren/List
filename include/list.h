#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include "list_config.h"


static const size_t LIST_DEFAULT_N_ELEMS  = 0;
static const size_t LIST_DEFAULT_CAPACITY = 8;
static const size_t LIST_CAPACITY_CHECK   = 4;
static const size_t LIST_CAPACITY_MUL     = 2;
static const size_t LIST_INVALID_ID       = 18446744073709551615ULL;


struct ListNode {
    ListElemT data;
    size_t prev_phys_id;
    size_t cur_phys_id;
    size_t next_phys_id;
};

struct List {
    size_t n_elems;
    size_t capacity;
    ListNode* elems;
    size_t head_phys_id;
    size_t tail_phys_id;
    size_t free_phys_id;
};

enum ListErrors {
    LIST_NO_ERRORS,
    LIST_ALLOC_ERROR,
    LIST_ABSENCE_OF_REQUIRED_ELEM
};


inline void ListConnectNodes(List* list, const size_t first_phys_id, const size_t second_phys_id);

inline void ListConnectArray(List* list, const size_t begin_phys_id, const size_t end_phys_id);

int ListCheckAndUpdateCapacity(List* list);

int ListPushFront(List* list, const ListElemT new_elem, size_t* phys_id);

int ListPushBack(List* list, const ListElemT new_elem, size_t* phys_id);

int ListAlloc(List* list);

void ListDestruct(List* list);

int ListGetByLogicId(List* list, const size_t logic_id, ListElemT* found);

int ListGetByPhysId(List* list, const size_t phys_id, ListElemT* found);


#endif /* list.h */
