#include <cassert>

#include "pet/PET.h"

int main() {
    PET pet;
    pet.insertEdge(1, 2, 3);
    pet.insertEdge(1, 2, 4);

    auto res = pet.queryEdge(1, 2);
    assert(res.has_value());
    assert(res.value() == 7);

    return 0;
}