#include <cassert>
#include <stdexcept>

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
    //assert(!isLeaf());  // 路由只能发生在内部节点
	if (isLeaf()) throw std::runtime_error("PETNode::next() called on a leaf node.");

    uint64_t bit = fp.prefixBits(depth_) & 1ULL;
    return bit == 0 ? left.get() : right.get();
}

int PETNode::doExpand() {
    if (!isLeaf()) {
        return left->doExpand() + right->doExpand();
    }

    //assert(isLeaf()); // 只能扩展叶子节点
    left = std::make_unique<PETNode>(depth_ + 1);
    right = std::make_unique<PETNode>(depth_ + 1);
    return 2;
}