// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BFS_BLOCK_MAPPING_MANAGER_H_
#define BFS_BLOCK_MAPPING_MANAGER_H_

#include <stdint.h>

#include "block_mapping.h"

namespace baidu {
namespace bfs {

class BlockMappingManager {
public :
    BlockMappingManager(int32_t bucket_num);
    ~BlockMappingManager();
    bool GetBlock(int64_t block_id, NSBlock* block);
    bool GetLocatedBlock(int64_t id, std::vector<int32_t>* replica, int64_t* block_size);
    bool ChangeReplicaNum(int64_t block_id, int32_t replica_num);
    void AddNewBlock(int64_t block_id, int32_t replica,
                     int64_t version, int64_t block_size,
                     const std::vector<int32_t>* init_replicas);
    bool UpdateBlockInfo(int64_t block_id, int32_t server_id, int64_t block_size,
                         int64_t block_version);
    void RemoveBlocksForFile(const FileInfo& file_info);
    void RemoveBlock(int64_t block_id);
    void DealWithDeadNode(int32_t cs_id, const std::set<int64_t>& blocks);
    StatusCode CheckBlockVersion(int64_t block_id, int64_t version);
    void PickRecoverBlocks(int32_t cs_id, int32_t block_num,
                           std::vector<std::pair<int64_t, std::set<int32_t> > >* recover_blocks,
                           int32_t* hi_num);
    void ProcessRecoveredBlock(int32_t cs_id, int64_t block_id);
    void GetCloseBlocks(int32_t cs_id, google::protobuf::RepeatedField<int64_t>* close_blocks);
    void GetStat(int32_t cs_id, RecoverBlockNum* recover_num);
    void ListRecover(RecoverBlockSet* recover_blocks);
    void SetSafeMode(bool safe_mode);
    void MarkIncomplete(int64_t block_id);
private:
    int32_t GetBucketOffset(int64_t block_id);
private:
    int32_t blockmapping_bucket_num_;
    std::vector<BlockMapping*> block_mapping_;
    ThreadPool* thread_pool_;
};

} // namespace bfs
} // namespace baidu

#endif
