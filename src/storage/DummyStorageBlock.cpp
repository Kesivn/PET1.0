#include"DummyStorageBlock.h"

bool DummyStorageBlock::insert(uint64_t key, uint64_t value) {
    data_[key] += value;
    return true;
}

std::optional<uint64_t> DummyStorageBlock::query(uint64_t key) {
    auto it = data_.find(key);
    if (it == data_.end()) return std::nullopt;
    return it->second;
}

bool DummyStorageBlock::isFull() const {
    return data_.size() > 1000000; // ¡Ÿ ±„–÷µ
}

