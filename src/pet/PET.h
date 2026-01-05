#pragma once

#include <memory>
#include <optional>

#include "storage/StorageBlock.h"
#include "PETNode.h"

class PET {
public:
    PET();

    bool insertEdge(uint64_t src, uint64_t dst, uint64_t weight = 1, uint64_t t_stamp = 0);

    std::optional<uint64_t> queryEdge(uint64_t src, uint64_t dst);

private:
    std::shared_ptr<StorageBlock> rootBlock_;

	std::unique_ptr<PETNode> root_;

    PETNode* routeToLeaf(const Fingerprint& fp);

private:
    static Fingerprint makeFingerprint(uint64_t src, uint64_t dst);
};