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
    int getmemory(){return mem;};
    ~GapFilter() {}
};
#endif