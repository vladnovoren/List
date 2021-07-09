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
    size_t prev_id;
    size_t cur_id;
    size_t next_id;
};

struct List {
    size_t n_elems;
    size_t capacity;
    ListNode* elems;
    size_t head_id;
    size_t tail_id;
    size_t free_id;
};

enum ListErrors {
    LIST_NO_ERRORS,
    LIST_ALLOC_ERROR
};


int ListAlloc(List* list);

void ListDestruct(List* list);


#endif /* list.h */
