#include <mpsc_queue.h>

#include <memory>
#include <iostream>

struct point {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, const point& p) {
    os << "point { x: " << p.x << ", y: " << p.y << " }";
    return os;
}

void test_shared() {
    auto shared_q = std::make_shared<mpsc::queue<point>>();
    auto shared_copy = shared_q;
    shared_q->push(point{1, 2});
    shared_q->push(point{3, 4});
    shared_q->push(point{5, 6});

    auto popped = shared_copy->pop();
    std::cout << "pop from copy: " << popped.value << std::endl;
    popped = shared_q->pop();
    std::cout << "pop from q: " << popped.value << std::endl;
    popped = shared_copy->pop();
    std::cout << "pop from copy: " << popped.value << std::endl;

    std::cout << "q is empty: " << std::boolalpha << shared_q->is_empty() << std::endl;
    std::cout << "copy is empty: " << std::boolalpha << shared_copy->is_empty() << std::endl;
}

int
main() {
    test_shared();
    return 0;
}