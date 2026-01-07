#pragma once

#include <unordered_map>
#include <functional>

#include "StorageBlock.h"

class DummyStorageBlock : public StorageBlock {
public:
    bool insert(uint64_t key, uint64_t value) override;

	//bool insert(uint64_t src, uint64_t dst, uint64_t weight) override;

    std::optional<uint64_t> query(uint64_t key) override;

	//std::optional<uint64_t> queryEdge(uint64_t key) override;

	//std::optional<uint64_t> queryNodeIN(uint64_t key) override;

    //std::optional<uint64_t> queryNodeOut(uint64_t key) override;

    bool isFull() const override;

    size_t size() const;

private:
    std::unordered_map<uint64_t, uint64_t> data_;
    const static size_t capacity_ = 100000;

public:
    void forEach(const std::function<void(uint64_t key, uint64_t value)>& visitor) const override;

	bool isUse() const override;
};