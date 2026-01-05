#include "PET.h"

#include <storage/DummyStorageBlock.h>

static uint64_t combine(uint64_t s, uint64_t d) {
    return (s << 32) ^ d;
}

PET::PET() {
    rootBlock_ = std::make_unique<DummyStorageBlock>();
}

bool PET::insertEdge(uint64_t src, uint64_t dst, uint64_t weight, uint64_t t_stamp) {
    uint64_t key = combine(src, dst);
    return rootBlock_->insert(key, weight);
}

std::optional<uint64_t> PET::queryEdge(uint64_t src, uint64_t dst) {
    uint64_t key = combine(src, dst);
    return rootBlock_->query(key);
}