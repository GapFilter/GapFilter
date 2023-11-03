#ifndef _GAPFILTER_STRAW_H
#define _GAPFILTER_STRAW_H

#include <x86intrin.h>
#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "Packet.h"
#include "GapFilter.h"
using namespace std;

class GapFilter_Straw : public GapFilter
{
public:
    const __m64 m64zero = {0};
    const __m128i m128zero = {0, 0};
    struct bucket{
    __m128i m128_fp;
    __m64 m64_seq;
    };
    const int MAXTURN = 8;
    uint64_t bucket_num, blockbound;
    bucket *table;
    BOBHash64 *hash_index1, *hash_index2, *hash_fp;

public:
    GapFilter_Straw(int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        bucket_num = (memory / (sizeof(uint32_t) + sizeof(Seq))) / 4;
        blockbound = bucket_num / 2;
        table = new bucket[bucket_num];
        for(uint64_t i = 0; i < bucket_num; i++){
            memset(&table[i], 0, sizeof(bucket));
        }

        srand(hash_seed);
        hash_index1 = new BOBHash64(rand()), hash_index2 = new BOBHash64(rand());
        hash_fp = new BOBHash64(rand());
    }
 
    bool Solution(const Packet &packet)
    {
        bool res = false; 
        uint32_t fp = (hash_fp->run((const char *)packet.id.data, FLOWID_LEN)) % (0x100000000ull);
        uint64_t index_1 = (hash_index1->run((const char *)&fp, sizeof(uint32_t))) % blockbound;
        uint64_t index_2 = (hash_index2->run((const char *)&fp, sizeof(uint32_t))) % blockbound + blockbound;
        bucket *b1 = &table[index_1], *b2 = &table[index_2];
        
        __m128i m128i_visitfp = (__m128i)_mm_set1_epi32(fp); 
        __m128i m128i_eqres_1, m128i_eqres_2;
        int tailzero_1, tailzero_2, matchplace_1, matchplace_2;
        m128i_eqres_1 = _mm_cmpeq_epi32(m128i_visitfp, b1->m128_fp);
        tailzero_1 = __tzcnt_u32(_mm_movemask_epi8(m128i_eqres_1));
        matchplace_1 = tailzero_1 / 4;
        if(matchplace_1 < 4){
            uint16_t *match_cell_seq = &(((uint16_t*)&b1->m64_seq)[matchplace_1]);
            uint16_t delta = packet.seq - *match_cell_seq;
            if (delta >= T1 && delta < T2)
                res = true;
            if(packet.seq > *match_cell_seq || *match_cell_seq - packet.seq >= THRES)
                *match_cell_seq = packet.seq;            
            return res;
        }

        m128i_eqres_2 = _mm_cmpeq_epi32(m128i_visitfp, b2->m128_fp);
        tailzero_2 = __tzcnt_u32(_mm_movemask_epi8(m128i_eqres_2));
        matchplace_2 = tailzero_2 / 4;
        if(matchplace_2 < 4){
            uint16_t *match_cell_seq = &(((uint16_t*)&b2->m64_seq)[matchplace_2]);
            uint16_t delta = packet.seq - *match_cell_seq;
            if (delta >= T1 && delta < T2)
                res = true;
            if(packet.seq > *match_cell_seq || *match_cell_seq - packet.seq >= THRES)
                *match_cell_seq = packet.seq;            
            return res;
        }

        m128i_eqres_1 = _mm_cmpeq_epi32(m128zero, b1->m128_fp);
        tailzero_1 = __tzcnt_u32(_mm_movemask_epi8(m128i_eqres_1));
        matchplace_1 = tailzero_1 / 4;
        if(matchplace_1 < 4){
            ((uint32_t*)&b1->m128_fp)[matchplace_1] = fp;
            ((uint16_t*)&b1->m64_seq)[matchplace_1] = packet.seq;
            return res;
        }

        m128i_eqres_2 = _mm_cmpeq_epi32(m128zero, b2->m128_fp);
        tailzero_2 = __tzcnt_u32(_mm_movemask_epi8(m128i_eqres_2));
        matchplace_2 = tailzero_2 / 4;
        if(matchplace_2 < 4){
            ((uint32_t*)&b2->m128_fp)[matchplace_2] = fp;
            ((uint16_t*)&b2->m64_seq)[matchplace_2] = packet.seq;
            return res;
        }

        uint64_t kick_index = index_1;
        if(rand()%2==0) kick_index = index_2;
        uint32_t insert_fp = fp;
        uint16_t insert_seq = packet.seq;
        for(int turn = 0; turn < MAXTURN; turn++){
            int kick_i = rand() % 4;
            uint32_t kick_fp = ((uint32_t*)&table[kick_index].m128_fp)[kick_i];
            uint16_t kick_seq = ((uint16_t*)&table[kick_index].m64_seq)[kick_i];
            ((uint32_t*)&table[kick_index].m128_fp)[kick_i] = insert_fp;
            ((uint16_t*)&table[kick_index].m64_seq)[kick_i] = insert_seq;

            if(kick_index < blockbound)
                kick_index = ((hash_index2->run((const char *)&kick_fp, sizeof(uint32_t)))) % blockbound + blockbound;
            else
                kick_index = ((hash_index1->run((const char *)&kick_fp, sizeof(uint32_t)))) % blockbound;
            __m128i m128_eqres = _mm_cmpeq_epi32(m128zero, table[kick_index].m128_fp);
            int tailzero = __tzcnt_u32(_mm_movemask_epi8(m128_eqres));
            int matchplace = tailzero / 4;
            if(matchplace < 4){
                ((uint32_t*)&table[kick_index].m128_fp)[matchplace] = kick_fp;
                ((uint16_t*)&table[kick_index].m64_seq)[matchplace] = kick_seq;
                return res;
            }
            insert_fp = kick_fp;
            insert_seq = kick_seq;
        }
        return res;
    }

    string Name()
    {
        return string("GapFilter_Straw");
    }
    ~GapFilter_Straw()
    {
        delete[] table;
        delete hash_index1, hash_index2;
        delete hash_fp;
    }
};

#endif