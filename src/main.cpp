#include "list_dump.h"


int main(int arc, char* argv[]) {

    List list = {};
    ListAlloc(&list);
    size_t id = 0;
    for (size_t i = 0; i < 4; ++i)
        ListPushBack(&list, 1, &id);
    
    FILE* log = fopen(argv[1], "wb");
    ListDump(&list, log);
    fclose(log);
    return 0;
}
