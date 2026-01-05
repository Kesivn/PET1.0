#pragma once

#include <memory>
#include <vector>

#include "storage/StorageBlock.h"
#include "fingerprint/Fingerprint.h"

class PETNode {
public:
    explicit PETNode(int depth);

    bool isLeaf() const;

    // 仅 PET 使用，不对外
    std::shared_ptr<StorageBlock> block;        // 叶子节点有效

    std::unique_ptr<PETNode> left;              // 前缀位 = 0
    std::unique_ptr<PETNode> right;             // 前缀位 = 1

    int depth() const {
        return depth_;
    }

private:
    int depth_;  // 当前节点使用的是 fingerprint 的第 depth_ 位
    //root节点的depth_=0，子节点依次递增

public:
    PETNode* next(const Fingerprint& fp);

};

/*
* 一个 PETNode 要么是叶子节点，要么是内部节点，不能两者兼有。
* 
*叶子节点：
*block != nullptr
*left == nullptr && right == nullptr
*
*内部节点：
*block == nullptr
*left != nullptr && right != nullptr
*/