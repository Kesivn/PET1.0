#include <cassert>

#include"PETNode.h"
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

    uint64_t bit = fp.prefixBits(depth_) & 1ULL;
    return bit == 0 ? left.get() : right.get();
}