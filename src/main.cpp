#include "list.h"


int main() {
    List list = {};
    ListAlloc(&list);
    size_t id = 0;
    for (size_t i = 0; i < 1000000; i++) {
        ListPushFront(&list, 1, &id);
    }
    ListDestruct(&list);
    return 0;
}
