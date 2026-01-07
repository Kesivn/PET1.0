#include <cassert>
#include<iostream>

#include "pet/PET.h"

int main() {
    PET pet;

    for (int i = 0; i < 300000; ++i) {
        pet.input(i, i + 1, 1);
    }
    int miss = 0;
    int wrong = 0;
    for (int i = 0; i < 150000; ++i) {
        auto res = pet.queryEdge(i, i + 1);
        if (!res.has_value()) miss++;
        else {
            if (res.value() != 1) {
                wrong++;
                //std::cout << i << " " << res.value() << std::endl;
            }
        }
    }

    if(miss) std::cout<<"[FAIL] Leaf invariant test, missed "<<miss<<" edges\n";
    if (wrong) std::cout << "[FAIL] Leaf invariant test, wrong " << wrong << " edges\n";
    if (!miss && !wrong)std::cout << "[PASS] Leaf invariant test\n";

    return 0;
}