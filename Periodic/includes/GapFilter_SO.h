#ifndef _GAPFILTER_SO_H
#define _GAPFILTER_SO_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "simd.h"
#include "Packet.h"
#include "GapFilter.h"
#include "Blacklist.h"

using namespace std;
class GapFilter_SO : public GapFilter
{
public:
    SIMD_Bucket_4_16 *bucket;
    uint64_t size;
    BOBHash64 *hash;
    Blacklist *blacklist;

public:
    GapFilter_SO(uint64_t memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        uint64_t BLmemory = memory * BLSIZE;        
        blacklist = new Blacklist(BLmemory, hash_seed);
        size = (memory - BLmemory) / (sizeof(Seq) * 4);
        bucket = new SIMD_Bucket_4_16[size];
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint64_t index=hash_value%size;
        uint16_t seq_offset=hash_value>>32;
        int res = bucket[index].Insert(packet.seq+seq_offset);
        
        if (res == 1)
            blacklist->Insert(packet);

        return res == 1;
    }

    void Report(map<FlowID, uint32_t> &blacklist_res)
    {
        blacklist->Report(blacklist_res);
        return;
    }

    string Name()
    {
        return string("GapFilter_SO");
    }
    ~GapFilter_SO()
    {
        delete hash;
        delete[] bucket;
        delete blacklist;
    }
};

#endif