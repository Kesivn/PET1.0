#pragma once

// 结构统计信息
// 用于描述 PET 树的结构性指标，便于监控和调试
struct StructureStats {
    int tree_depth;                 // 当前最大深度（从根节点 depth=0 开始），用于评估树的增长情况
    size_t block_count;             // StorageBlock 总数（叶子节点持有的块数），用于内存/存储资源监控
    size_t leaf_count;              // 叶节点数量（实际存储数据的节点数），用于评估分布密度
};

// 拓展（Expansion）相关统计
// 记录扩展操作的执行次数和效果，用于分析扩展策略的有效性
struct ExpansionStats {             //拓展统计
    size_t expand_total;            // 扩展触发的总次数（包括成功与失败的尝试）
    size_t expand_effective;        // 有效扩展次数（实际发生了节点分裂）
    size_t expand_ineffective;      // 无效扩展次数（尝试扩展但未改变结构）
    size_t expand_failed;           // 扩展后仍插入失败的次数（扩展后仍无法容纳新数据）
};

// 操作相关统计（插入、延迟等）
struct OperationStats {
    size_t insert_total;            // 插入总数（所有尝试，不论成功与否）
    size_t insert_success;          // 成功插入次数
    //size_t insert_delay;            // 插入时延   目前为时过早
    size_t query_total;                 // 查询总数
};

// 查询结果相关统计
// 用于衡量 PET 在查询语义上的准确性（误报/漏报/值错误等）
/*struct ResultStates {
    
	//size_t false_positive_count;        // 误报计数（报告存在但实际不存在）
	//size_t false_negative_count;        // 漏报计数（查询失败但实际存在）
    //size_t value_error;                 // 值不一致计数（返回的聚合/权重与实际期望不符）
};*/

// 存储层相关统计（负载因子等）
struct StorageStats {
    double avg_load_factor;             // 平均负载因子（各 StorageBlock 的平均装载比例），用于评估空间利用率
    double max_load_factor;             // 最大负载因子（某个 StorageBlock 的最大装载比例），用于检测热点或溢出风险
};

// 内存相关统计
struct MemoryStats {
    //size_t total_memory_bytes;          // 整个 PET 结构所占内存（字节），供监控和内存配额使用
    //size_t storage_block_memory_bytes;  // 所有 StorageBlock 占用的内存（字节），用于区分索引开销与存储开销
	size_t memory_in_theory;            //理论内存使用量
	double r_memory_save_in_theory;     //相对于理论内存的节省率
	//double memory_utilization;          // 内存利用率
};

// 汇总统计结构
// 将各类统计聚合在一起，方便上报和持久化
struct PETStats {
    StructureStats structure;           // 结构层面统计
    ExpansionStats expansion;           // 拓展相关统计
    OperationStats operation;           // 操作相关统计
    //ResultStates results;               // 查询结果统计
	MemoryStats memory;                  // 内存统计
    StorageStats storage;               // 存储统计
};