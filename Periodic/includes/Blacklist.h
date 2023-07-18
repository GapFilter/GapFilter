#ifndef _BLACKLIST_H
#define _BLACKLIST_H

#include <bits/stdc++.h>
#include "BOBHash.h"
#include "params.h"
#include "Packet.h"
using namespace std;

class Blacklist
{
public:
    struct entry
    {
        FlowID flowID;
        uint16_t freq;
		entry(){freq = 0;}
    };
	entry* blacklist;	
	uint32_t size;
	BOBHash *hash1,* hash2;
	int probing_times;

public:
	Blacklist(int BLmemory, int hash_seed = 1000, int pb_times = 5)
	{
		size = BLmemory / 15;
		blacklist = new entry[size];
		memset(blacklist, 0, sizeof(entry) * size);
		hash1 = new BOBHash(hash_seed);
		hash2 = new BOBHash((hash_seed + 599) % 1201);
		probing_times = pb_times;
	}

	void Insert(const Packet &packet)
	{
        uint32_t index = hash1->run((const char *)packet.id.data, FLOWID_LEN) % size;
        uint32_t delta = hash2->run((const char *)packet.id.data, FLOWID_LEN) % size;
		int times = 0;
		bool flag = 0;
		uint32_t empty_index = 0xffffffff;
		while(times < probing_times)
		{
			if(blacklist[index].flowID == packet.id){
				++ blacklist[index].freq;
				flag = 1;
				break;
			}
			if(blacklist[index].flowID.empty())
				empty_index = index;
			++ times;
			index = (index + delta) % size;
		}
		if(!flag && empty_index != 0xffffffff)
		{
			blacklist[empty_index].flowID = packet.id;
			++ blacklist[empty_index].freq;
		}
	}

	void Report(map<FlowID, uint32_t> &blacklist_res)
	{
		for(int i = 0; i < size; ++ i)
		{
			entry nowEntry = blacklist[i];
			if(!nowEntry.flowID.empty())
				blacklist_res[nowEntry.flowID] = nowEntry.freq;
		}
		memset(blacklist, 0, sizeof(entry) * size);
	}

	~Blacklist()
	{
		delete[] blacklist;
		delete hash1;
		delete hash2;
	}
};
#endif