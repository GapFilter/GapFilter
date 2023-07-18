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
    struct cell
    {
        FlowID flowID;
        Seq seq;
        Pointer nextid;
    };
    cell *table;
    uint64_t size;
    uint64_t basesize;
    Pointer nowid;
    BOBHash64 *hash;

public:
    GapFilter_Straw(uint64_t memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        size = memory / STRAWCELLSIZE;
        basesize = size * BASESIZE;
        nowid = basesize;
        table = new cell[size];
        memset(table, 0, sizeof(cell) * size);
        for(uint64_t i = 0; i < size; i++){
            table[i].nextid = -1;
        }
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        bool res = false; 
        uint64_t hash_value = hash->run((char *)packet.id.data, FLOWID_LEN);
        uint64_t bucket = hash_value % basesize, rand = hash_value >> 32;
        uint64_t index = bucket;
        int cnt = 1;
        while(!(table[index].flowID == packet.id) && table[index].nextid != -1){
            index = table[index].nextid;
            cnt ++;
        }
        if (table[index].flowID == packet.id){
            uint16_t delta = packet.seq - table[index].seq;
            if (delta >= T1 && delta < T2)
                res = true;
            if(packet.seq > table[index].seq || table[index].seq - packet.seq >= THRES)
                table[index].seq = packet.seq;
        }
        else{
            if(nowid < size){
                table[index].nextid = nowid;
                table[nowid].flowID = packet.id;
                table[nowid].seq = packet.seq;
                table[nowid].nextid = -1;
                nowid ++;
            }
            else{
                cnt = rand % cnt;
                while(cnt > 0 && table[index].nextid != -1){
                    index = table[index].nextid;
                    cnt --;
                }
                table[index].flowID = packet.id;
                table[index].seq = packet.seq;
            }
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
        delete hash;
    }
};

#endif