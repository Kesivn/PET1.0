#include"DummyStorageBlock.h"

bool DummyStorageBlock::insert(uint64_t key, uint64_t value) {
    auto it = data_.find(key);
    if (it != data_.end()) {
        it->second += value;
        return true;
    }

    if (isFull()) return false;

    data_.emplace(key, value);
    return true;
}

std::optional<uint64_t> DummyStorageBlock::query(uint64_t key) {
    auto it = data_.find(key);
    if (it == data_.end()) return std::nullopt;
    return it->second;
}

bool DummyStorageBlock::isFull() const {
    return data_.size() >= capacity_; // ¡Ÿ ±„–÷µ
}

size_t DummyStorageBlock::size() const {
    return data_.size();
}

void DummyStorageBlock::forEach(const std::function<void(uint64_t key, uint64_t value)>& visitor) const
{
    for (const auto &p : data_) {
        visitor(p.first, p.second);
    }
}

bool DummyStorageBlock::isUse() const
{
    return data_.size() > 0;
}

