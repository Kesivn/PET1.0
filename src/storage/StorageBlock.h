#pragma once
#include <optional>

class StorageBlock {
public:
    virtual bool insert(uint64_t key, uint64_t value) = 0;

    virtual std::optional<uint64_t> query(uint64_t key) = 0;

    virtual bool isFull() const = 0;

    virtual ~StorageBlock() = default;

};