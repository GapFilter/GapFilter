#ifndef _GAPFILTER_SO4_H
#define _GAPFILTER_SO4_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "simd.h"
#include "Packet.h"
#include "GapFilter.h"

using namespace std;
class GapFilter_SO4 : public GapFilter
{
public:
    SIMD_Bucket_4_16 *bucket;
    int size;
    BOBHash64 *hash;

public:
    GapFilter_SO4(int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        size = memory / (sizeof(uint16_t) * 4);
        bucket = new SIMD_Bucket_4_16[size];
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint32_t index=hash_value%size;
        uint16_t seq_offset=hash_value>>32;
        int res = bucket[index].Insert(packet.seq+seq_offset);
        return res == 1;
    }

    string Name()
    {
        return string("GapFilter_SO4");
    }
    ~GapFilter_SO4()
    {
        delete hash;
        delete[] bucket;
    }
};

#endif