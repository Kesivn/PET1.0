#pragma once

#include <memory>
#include <optional>
#include <cassert>

#include "storage/StorageBlock.h"
#include "PETNode.h"

struct PETConfig {
    size_t block_capacity = 100000;
    int max_depth = -1;
};

class PET {
public:
    PET();

    void input(uint64_t src, uint64_t dst, uint64_t weight = 1, uint64_t t_stamp = 0);

    bool insertEdge(uint64_t src, uint64_t dst, uint64_t weight = 1, uint64_t t_stamp = 0);

    std::optional<uint64_t> queryEdge(uint64_t src, uint64_t dst);

private:
	std::unique_ptr<PETNode> root_;

    PETNode* routeToLeaf(const Fingerprint& fp);

private:
    static Fingerprint makeFingerprint(uint64_t src, uint64_t dst);

    enum class PETState {
        normal,
        expanding
    };

	PETState state_ = PETState::normal;

private:
    bool inNormalState() const;

    void doExpand();

private:
    int prefix_depth_ = 0;

    PETConfig config_;

};