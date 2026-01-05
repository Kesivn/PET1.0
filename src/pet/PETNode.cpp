#include"PETNode.h"

PETNode::PETNode(int depth)
    : depth_(depth) {
}

bool PETNode::isLeaf() const {
    return !left && !right;
}

PETNode* PETNode::next(const Fingerprint& fp) {
    uint64_t bit = fp.prefixBits(depth_) & 1ULL;
    return bit == 0 ? left.get() : right.get();
}