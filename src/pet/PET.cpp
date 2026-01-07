#include "PET.h"
#include <iostream>

static uint64_t combine(uint64_t s, uint64_t d) {
    return (s << 32) ^ d;
}

PET::PET() {
    root_ = std::make_unique<PETNode>(0);
}

void PET::input(uint64_t src, uint64_t dst, uint64_t weight, uint64_t t_stamp)
{
    if (insertEdge(src, dst, weight, t_stamp)) { 
		stats_.operation.insert_success += 1;
        return; 
    }
    if (inNormalState()) {
        doExpand();
        bool success = insertEdge(src, dst, weight, t_stamp);
        if(success) {
            stats_.expansion.expand_effective += 1;
            stats_.operation.insert_success += 1;
        } 
        else {
            stats_.expansion.expand_failed += 1;
		}
	}
}

bool PET::insertEdge(uint64_t src, uint64_t dst, uint64_t weight, uint64_t t_stamp) {
	Fingerprint fp = makeFingerprint(src, dst);

    PETNode* node = root_.get();

    for (int depth = 0; depth <= prefix_depth_; ++depth) {
        if (!node) break;
        if (node->block) {
            if (node->block->insert(fp.raw(), weight)) return true;
        }
        if (depth == prefix_depth_) break;
        if (node->isLeaf()) break;
        node = node->next(fp);
    }

	stats_.operation.insert_total += 1;
    return false;
}

std::optional<uint64_t> PET::queryEdge(uint64_t src, uint64_t dst) {
    Fingerprint fp = makeFingerprint(src, dst);

    PETNode* node = root_.get();

    for (int depth = 0; depth <= prefix_depth_; ++depth) {
        if (!node) break;
        if (node->block) {
            auto res = node->block->query(fp.raw());
            if (res) return res;
        }
        if (depth == prefix_depth_) break;
        if (node->isLeaf()) break;
        node = node->next(fp);
    }
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
    if (int add_nums=root_->doExpand() > 0) {
        prefix_depth_ += 1;

        stats_.structure.tree_depth = prefix_depth_;
        stats_.structure.leaf_count += add_nums;
		stats_.structure.block_count += add_nums;

        stats_.expansion.expand_total += 1;
    }
	state_ = PETState::normal;
}

void PET::calculate_load_factor()
{
    size_t total_entries = 0;
    size_t total_capacity = 0;
    double max_load = 0.0;
    std::function<void(const PETNode*)> traverse = [&](const PETNode* node) {
        if (node->isLeaf()) {
            size_t block_size = 0;
            size_t block_capacity = config_.block_capacity;
            node->block->forEach([&](uint64_t key, uint64_t value) {
                block_size += 1;
            });
            total_entries += block_size;
            total_capacity += block_capacity;
            double load_factor = static_cast<double>(block_size) / block_capacity;
            if (load_factor > max_load) {
                max_load = load_factor;
            }
        } else {
            traverse(node->left.get());
            traverse(node->right.get());
        }
    };
    traverse(root_.get());
    stats_.storage.avg_load_factor = total_capacity == 0 ? 0.0 : static_cast<double>(total_entries) / total_capacity;
	stats_.storage.max_load_factor = max_load;
}

void PET::calculate_all()
{
    calculate_load_factor();
	stats_.memory.memory_in_theory = stats_.structure.block_count * config_.block_capacity * (sizeof(uint64_t) + sizeof(uint64_t));
	stats_.memory.r_memory_save_in_theory = 1.0 - (static_cast<double>(stats_.operation.insert_success) / (stats_.structure.block_count * config_.block_capacity));
}

PETStats PET::getStats() const
{
    return PETStats();
}

void PET::printStats() const
{
    PETStats stats = stats_;
    std::cout << "=== PET Statistics ===" << std::endl;
    std::cout << "Structure:" << std::endl;
    std::cout << "  Tree Depth: " << stats.structure.tree_depth << std::endl;
    std::cout << "  Block Count: " << stats.structure.block_count << std::endl;
    std::cout << "  Leaf Count: " << stats.structure.leaf_count << std::endl;
    std::cout << "Expansion:" << std::endl;
    std::cout << "  Total Expansions: " << stats.expansion.expand_total << std::endl;
    std::cout << "  Effective Expansions: " << stats.expansion.expand_effective << std::endl;
    std::cout << "  Ineffective Expansions: " << stats.expansion.expand_ineffective << std::endl;
    std::cout << "  Failed Expansions: " << stats.expansion.expand_failed << std::endl;
    std::cout << "Operation:" << std::endl;
    std::cout << "  Total Inserts: " << stats.operation.insert_total << std::endl;
    std::cout << "  Successful Inserts: " << stats.operation.insert_success << std::endl;
    std::cout << "  Total Queries: " << stats.operation.query_total << std::endl;
    std::cout << "Storage:" << std::endl;
    std::cout << "  Average Load Factor: " << stats.storage.avg_load_factor << std::endl;
    std::cout << "  Maximum Load Factor: " << stats.storage.max_load_factor << std::endl;
    std::cout << "Memory:" << std::endl;
    std::cout << "  Theoretical Memory Usage: " << stats.memory.memory_in_theory << " bytes" << std::endl;
	std::cout << "  Relative Memory Savings: " << stats.memory.r_memory_save_in_theory * 100.0 << "%" << std::endl;
}
