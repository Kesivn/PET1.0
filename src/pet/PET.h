#pragma once

#include <memory>
#include <optional>

#include "storage/StorageBlock.h"

class PET {
public:
    PET();

    bool insertEdge(uint64_t src, uint64_t dst, uint64_t weight = 1, uint64_t t_stamp = 0);

    std::optional<uint64_t> queryEdge(uint64_t src, uint64_t dst);

private:
    std::unique_ptr<StorageBlock> rootBlock_;
};