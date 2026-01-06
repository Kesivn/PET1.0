#include "PET.h"

static uint64_t combine(uint64_t s, uint64_t d) {
    return (s << 32) ^ d;
}

PET::PET() {
    root_ = std::make_unique<PETNode>(0);
}

void PET::input(uint64_t src, uint64_t dst, uint64_t weight, uint64_t t_stamp)
{
    if (insertEdge(src, dst, weight, t_stamp)) return;
    if (inNormalState()) {
        doExpand();
        bool success = insertEdge(src, dst, weight, t_stamp);
        assert(success); // 扩展后应当能插入成功
	}
}

bool PET::insertEdge(uint64_t src, uint64_t dst, uint64_t weight, uint64_t t_stamp) {
	Fingerprint fp = makeFingerprint(src, dst);

    PETNode* node = routeToLeaf(fp);//路由

    if(node->block)
        return node->block->insert(fp.raw(), weight);
    return false;
}

std::optional<uint64_t> PET::queryEdge(uint64_t src, uint64_t dst) {
    Fingerprint fp = makeFingerprint(src, dst);

    PETNode* node = routeToLeaf(fp);

    if(node->block)
        return node->block->query(fp.raw());
    return std::nullopt;
}

PETNode* PET::routeToLeaf(const Fingerprint& fp) {
	auto node = root_.get();
    while (!node->isLeaf()) {
		node = node->next(fp);
    }
    return node;
}

Fingerprint PET::makeFingerprint(uint64_t src, uint64_t dst)
{
    uint64_t tsr = src;
    tsr ^= dst + 0x9e3779b97f4a7c15ULL + (tsr << 6) + (tsr >> 2);
    //这是一个临时的哈希模拟
	return Fingerprint(tsr, 64);
}

bool PET::inNormalState() const
{
    return state_ == PETState::normal;
}

void PET::doExpand()
{
    state_ = PETState::expanding;
    root_->doExpand();
	state_ = PETState::normal;
}
