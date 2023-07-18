#ifndef _GAPFILTER_H
#define _GAPFILTER_H

#include <bits/stdc++.h>
#include "BOBHash64.h"
#include "params.h"
#include "Packet.h"
using namespace std;

class GapFilter
{
public:
    int mem;
    GapFilter(int memory) : mem(memory) {}
    virtual bool Solution(const Packet &packet) { return 1; };
    virtual string Name() { return (string) ""; }
    virtual void Report(map<FlowID, uint32_t> &blacklist_res) = 0;
    int getmemory(){return mem;};
    ~GapFilter() {}
};
#endif