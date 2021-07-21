#include "list.h"


int main() {
    for (size_t k = 0; k < 1; ++k) {
        List list = {};
        ListAlloc(&list);
        size_t id = 0;
        for (size_t i = 0; i < 500000; i++) {
            ListPushFront(&list, 1, &id);
            ListPushBack(&list, 1, &id);
        }
        ListDestruct(&list);
    }
    return 0;
}
