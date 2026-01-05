#pragma once

#include <unordered_map>

#include "StorageBlock.h"

class DummyStorageBlock : public StorageBlock {
public:
    bool insert(uint64_t key, uint64_t value) override;

    std::optional<uint64_t> query(uint64_t key) override;

    bool isFull() const override;

private:
    std::unordered_map<uint64_t, uint64_t> data_;
};