#include <list>

int main() {
    std::list<int> my_list;
    for (size_t i = 0; i < 1000000; i++)
        my_list.push_front(1);
    return 0;
}