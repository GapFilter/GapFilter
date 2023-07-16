#ifndef _GAPFILTER_SO2_H
#define _GAPFILTER_SO2_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "simd.h"
#include "Packet.h"
#include "GapFilter.h"
 
using namespace std;
class GapFilter_SO2 : public GapFilter
{
public:
    SIMD_Bucket_2_16 *bucket;
    int size;
    BOBHash64 *hash;

public:
    GapFilter_SO2(int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        size = memory / (sizeof(uint16_t) * 2);
        bucket = new SIMD_Bucket_2_16[size];
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet) // 返回是否发生断流
    {
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint32_t index=hash_value%size;
        uint16_t seq_offset=hash_value>>32;        
        int bucket_res = bucket[index].Insert(packet.seq+seq_offset);
        return bucket_res == 1;
    }

    string Name()
    {
        return string("GapFilter_SO2");
    }
    ~GapFilter_SO2()
    {
        delete hash;
        delete[] bucket;
    }
};

#endif