#ifndef _GAPFILTER_AO_WOSIMD_H
#define _GAPFILTER_AO_WOSIMD_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "wosimd.h"
#include "Packet.h"
#include "GapFilter.h"

using namespace std;

class GapFilter_AO_woSIMD : public GapFilter
{
public:
    woSIMD_Bucket_8_16_fpn *bucket;
    uint64_t size;
    uint32_t fpbit, sus;
    BOBHash64 *hash;

public:
    GapFilter_AO_woSIMD(uint32_t fpbit_, uint32_t sus_, uint64_t memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        fpbit = fpbit_;
        sus = sus_;
        size = memory / (AOBUCKETSIZE * (sizeof(Seq) + fpbit/8));
        bucket = (woSIMD_Bucket_8_16_fpn*)operator new(size*sizeof(woSIMD_Bucket_8_16_fpn));
        for(uint64_t i = 0; i < size; ++i){
            new (bucket+i)woSIMD_Bucket_8_16_fpn(sus_);
        }
        memset(bucket, 0, sizeof(woSIMD_Bucket_8_16_fpn) * size);
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint64_t index = hash_value % size;
        uint16_t seq_offset = hash_value >> 32;
        uint16_t fp = (hash_value >> 48) % (1 << fpbit);
        int res = bucket[index].Insert(packet.seq+seq_offset, fp);
        return res == 1;
    }

    string Name()
    {
        char buf[64];
        sprintf(buf, "GapFilter_AO_woSIMD");
        return string(buf);
    }

    ~GapFilter_AO_woSIMD()
    {
        delete hash;
        delete[] bucket;
    }
};

#endif