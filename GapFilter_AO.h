#ifndef _GAPFILTER_AO_H
#define _GAPFILTER_AO_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "simd.h"
#include "Packet.h"
#include "GapFilter.h"

using namespace std;
 
class GapFilter_AO : public GapFilter
{
public:
    SIMD_Bucket_8_16_fpn *bucket;
    int size;
    uint32_t fpbit, sus;
    BOBHash64 *hash;

public:
    GapFilter_AO(int fpbit_, int sus_, int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        fpbit = fpbit_;
        sus = sus_;
        size = memory / (AOBUCKETSIZE * sizeof(uint16_t) + fpbit);
        bucket = new SIMD_Bucket_8_16_fpn[size];
        memset(bucket, 0, sizeof(SIMD_Bucket_8_16_fpn) * size);
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint32_t index=hash_value%size;
        uint16_t seq_offset=hash_value>>32;
        uint16_t fp=(hash_value>>48)%(1<<fpbit);
        int res = bucket[index].Insert(packet.seq+seq_offset, fp, sus);
        return res == 1;
    }

    string Name()
    {
        char buf[64];
        sprintf(buf, "GapFilter_AO_sus_%d_nor_%d", sus, AOBUCKETSIZE - sus);
        return string(buf);
    }

    ~GapFilter_AO()
    {
        delete hash;
        delete[] bucket;
    }
};

#endif