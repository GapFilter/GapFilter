#ifndef _GAPFILTER_STRAW_H
#define _GAPFILTER_STRAW_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "Packet.h"
#include "GapFilter.h"
using namespace std;

class GapFilter_straw : public GapFilter
{
public:
    struct cell
    {
        FlowID flowID;
        uint16_t seq;
        int nextid;
    };
    int size;
    int basesize;
    int nowid;
    cell *table;
    BOBHash64 *hash;

public:
    GapFilter_straw(int memory, int hash_seed = 1000)
        : GapFilter(memory)
    {
        size = memory / STRAWCELLSIZE;
        basesize = size * BASESIZE;
        nowid = basesize;
        table = new cell[size];
        memset(table, 0, sizeof(cell) * size);
        for(int i = 0; i < size; i++){
            table[i].nextid = -1;
        }
        hash = new BOBHash64(hash_seed);
    }

    bool Solution(const Packet &packet)
    {
        bool res = false; 
        uint32_t index = (hash->run((const char *)packet.id.data, FLOWID_LEN)) % basesize;
        
        while(!(table[index].flowID == packet.id) && table[index].nextid != -1){
            index = table[index].nextid;
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
                table[index].flowID = packet.id;
                table[index].seq = packet.seq;
            }
        }
        return res;
    }

    string Name()
    {
        return string("GapFilter_straw");
    }

    ~GapFilter_straw()
    {
        delete[] table;
        delete hash;
    }
};

#endif