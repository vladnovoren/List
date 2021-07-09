#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include "list_config.h"

struct List {
    size_t n_elems;
    size_t capacity;
    ListElemT* elems;
};

enum ListErrors {
    LIST_NO_ERRORS,
    LIST_ALLOC_ERROR
};


int 


#endif /* list.h */