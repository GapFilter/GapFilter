#ifndef _GAPFILTER_STRAW_H
#define _GAPFILTER_STRAW_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "Packet.h"
#include "GapFilter.h"
using namespace std;

class GapFilter_Straw : public GapFilter
{
public:
    struct cell{
        uint64_t fingerprint;
        Seq seq;};
    typedef cell* bucket;
    const int bucket_size=4, fp_length=32;
    const int MAXTURN=8;
    uint64_t bucket_num, blockbound;
    bucket *table;
    BOBHash64 *hash_index1, *hash_index2, *hash_fp;

public:
    GapFilter_Straw(int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        bucket_num = (memory / (fp_length/8 + sizeof(Seq))) / bucket_size;
        blockbound = bucket_num / 2;
        table = new bucket[bucket_num];
        for(uint64_t i = 0; i < bucket_num; i++){
            table[i] = new cell[bucket_size];
            memset(table[i], 0, sizeof(cell) * bucket_size);
        }

        srand(hash_seed);
        hash_index1 = new BOBHash64(rand()), hash_index2 = new BOBHash64(rand());
        hash_fp = new BOBHash64(rand());
    }

    bool Solution(const Packet &packet)
    {
        bool res = false; 
        uint64_t fp = (hash_fp->run((const char *)packet.id.data, FLOWID_LEN)) % (0x1ull << fp_length);
        uint64_t index_1 = (hash_index1->run((const char *)&fp, sizeof(uint64_t))) % blockbound;
        uint64_t index_2 = (hash_index2->run((const char *)&fp, sizeof(uint64_t))) % blockbound + blockbound;
        
        bucket b1 = table[index_1], b2 = table[index_2];
        cell *match_cell = NULL, *empty_cell = NULL;

        for(int i = 0; i < bucket_size; i++){
            if(b1[i].fingerprint == fp){
                match_cell = &b1[i];
                goto find;
            }
            if(empty_cell == NULL && b1[i].fingerprint == 0 && b1[i].seq == 0){
                empty_cell = &b1[i];
            }
        }
        for(int i = 0; i < bucket_size; i++){
            if(b2[i].fingerprint == fp){
                match_cell = &b2[i];
                goto find;
            }
            if(empty_cell == NULL && b2[i].fingerprint == 0 && b2[i].seq == 0){
                empty_cell = &b2[i];
            }
        }

        if(empty_cell != NULL){
            empty_cell->fingerprint = fp;
            empty_cell->fingerprint = packet.seq;
        }
        else{
            uint64_t kick_index = index_1;
            if(rand()%2==0) kick_index = index_2;

            uint64_t insert_fp = fp;
            Seq insert_seq = packet.seq;
            for(int turn = 0; turn < MAXTURN; turn++){
                int kick_i = rand() % bucket_size;
                cell* kick_cell = &table[kick_index][kick_i];
                uint64_t kick_fp = kick_cell->fingerprint;
                Seq kick_seq = kick_cell->seq;
                kick_cell->fingerprint = insert_fp;
                kick_cell->seq = insert_seq;

                if(kick_index < blockbound)
                    kick_index = ((hash_index2->run((const char *)&kick_fp, sizeof(uint64_t)))) % blockbound + blockbound;
                else
                    kick_index = ((hash_index1->run((const char *)&kick_fp, sizeof(uint64_t)))) % blockbound;
                for(int i = 0; i < bucket_size; i++){
                    if(table[kick_index][i].fingerprint == 0 && table[kick_index][i].seq == 0){
                        table[kick_index][i].fingerprint = kick_fp;
                        table[kick_index][i].seq = kick_seq;
                        return res;
                    }
                }
                insert_fp = kick_fp;
                insert_seq = kick_seq;
            }
        }
        return res;

find:
        uint16_t delta = packet.seq - match_cell->seq;
        if (delta >= T1 && delta < T2)
            res = true;
        if(packet.seq > match_cell->seq || match_cell->seq - packet.seq >= THRES)
            match_cell->seq = packet.seq;

        return res;
    }
 
    string Name()
    {
        return string("GapFilter_Straw");
    }

    ~GapFilter_Straw()
    {
        for(uint64_t i = 0; i < bucket_num; i++)
            delete[] table[i];
        delete[] table;
        delete hash_index1, hash_index2;
        delete hash_fp;
    }
};

#endif