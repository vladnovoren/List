#include <list>

int main() {
    for (size_t k = 0; k < 1000; ++k) {
        std::list<int> my_list;
        for (size_t i = 0; i < 1000000; i++)
            my_list.push_front(1);
    }
    return 0;
}