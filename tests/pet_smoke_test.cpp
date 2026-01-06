#include <cassert>
#include<iostream>

#include "pet/PET.h"

int main() {
    PET pet;

    for (int i = 0; i < 1000000; ++i) {
        if (!pet.insertEdge(i, i + 1, 1)) assert(i);
    }

    for (int i = 0; i < 1000000; ++i) {
        auto res = pet.queryEdge(i, i + 1);
        assert(res.has_value());
        assert(res.value() == 1);
    }

    std::cout << "[PASS] Leaf invariant test\n";

    return 0;
}