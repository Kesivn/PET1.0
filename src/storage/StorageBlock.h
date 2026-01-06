#pragma once
#include <optional>
#include <functional>

class StorageBlock {
public:
    virtual bool insert(uint64_t key, uint64_t value) = 0;

    //virtual bool insert(uint64_t src, uint64_t dst, uint64_t weight) = 0;

    virtual std::optional<uint64_t> query(uint64_t key) = 0;

    //virtual std::optional<uint64_t> queryEdge(uint64_t key) = 0;

    //virtual std::optional<uint64_t> queryNodeIN(uint64_t key) = 0;

    //virtual std::optional<uint64_t> queryNodeOut(uint64_t key) = 0;

    virtual bool isFull() const = 0;

    virtual ~StorageBlock() = default;

    virtual void forEach(const std::function<void(uint64_t key, uint64_t value)>& visitor) const = 0;

};