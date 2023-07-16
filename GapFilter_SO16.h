#ifndef _GAPFILTER_SO16_H
#define _GAPFILTER_SO16_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "simd.h"
#include "Packet.h"
#include "GapFilter.h"

using namespace std;
class GapFilter_SO16 : public GapFilter
{
public:
    SIMD_Bucket_16_16 *bucket;
    int size;
    BOBHash64 *hash;

public:
    GapFilter_SO16(int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        size = memory / (sizeof(uint16_t) * 16);
        bucket = new SIMD_Bucket_16_16[size];
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint32_t index=hash_value%size;
        uint16_t seq_offset=hash_value>>32;
        int bucket_res = bucket[index].Insert(packet.seq+seq_offset);
        return bucket_res == 1;
    }

    string Name()
    {
        return string("GapFilter_SO16");
    }
    ~GapFilter_SO16()
    {
        delete hash;
        delete[] bucket;
    }
};

#endif