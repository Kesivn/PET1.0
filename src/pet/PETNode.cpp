#include <cassert>

#include "PETNode.h"
#include "storage/DummyStorageBlock.h"

PETNode::PETNode(int depth)
    : depth_(depth) {
    block = std::make_shared<DummyStorageBlock>();
}

bool PETNode::isLeaf() const {
    return !left && !right;
}

PETNode* PETNode::next(const Fingerprint& fp) {
    assert(!isLeaf());  // 路由只能发生在内部节点

    uint64_t bit = fp.prefixBits(depth_) & 1ULL;
    return bit == 0 ? left.get() : right.get();
}

void PETNode::doExpand() {
    if (!isLeaf()) {
        left->doExpand();
        right->doExpand();
        return;
    }

    //assert(isLeaf()); // 只能扩展叶子节点
    left = std::make_unique<PETNode>(depth_ + 1);
    right = std::make_unique<PETNode>(depth_ + 1);

    if (block) {
        block->forEach([&](uint64_t key, uint64_t value) {
            Fingerprint fp(key, 64);
            uint64_t bit = fp.prefixBits(depth_) & 1ULL;
            if (bit == 0) {
                left->block->insert(key, value);
            } else {
                right->block->insert(key, value);
            }
        });
    }
    block.reset();
}