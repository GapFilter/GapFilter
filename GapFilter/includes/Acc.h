#ifndef _ACC_H
#define _ACC_H

#include <bits/stdc++.h>
#include "Packet.h"
#include "params.h"
#include "GapFilter.h"
using namespace std;
 
class Acc
{
public:
    uint64_t TP = 0;
    uint64_t FP = 0;
    uint64_t TN = 0;
    uint64_t FN = 0;
    double PR = 0;
    double RR = 0;
    double AC = 0;
    double F1 = 0;
    void calc()
    {
        PR = (double)TP / (TP + FP);
        RR = (double)TP / (TP + FN);
        AC = (double)(TP + TN) / (TP + FP + TN + FN);
        F1 = 2 * PR * RR / (PR + RR);
    }
    void Print()
    {
        cout << "TP=" << TP << endl;
        cout << "FP=" << FP << endl;
        cout << "TN=" << TN << endl;
        cout << "FN=" << FN << endl;
        cout << "F1=" << F1 << endl;
        cout << "PR=" << PR << endl;
        cout << "RR=" << RR << endl;
        cout << "AC=" << AC << endl;
    }
};

uint64_t Load(vector<Packet> &dataset, char* path, int64_t readnum = -1)
{
    dataset.clear();
    cout << "Loading" << path << "..." << endl << flush;
    ifstream datainput(path);
    if(!datainput.is_open()){
        printf("load dataset error\n");
        exit(0);
    }
    Packet packet;
    int64_t packcnt = 0;
    while (datainput >> packet.id >> packet.seq >> packet.time)
    {
        dataset.push_back(packet);
        if (++packcnt == readnum)
            break;
    }
    datainput.close();
    return packcnt;
}

void GenStandard(vector<bool> &standard, vector<Packet> &dataset){
    map<FlowID, uint16_t> mp;
    uint64_t cnt = 0;
    mp.clear();
    for(auto packet : dataset)
    {
        uint16_t oldseq = 0;
        cnt++;
        if (!mp.count(packet.id))
        {
            standard.push_back(false);
            mp[packet.id] = packet.seq;
        }
        else
        {
            oldseq = mp[packet.id];
            if (packet.seq > oldseq || oldseq - packet.seq >= 10000)
                mp[packet.id] = packet.seq;
            if ((uint16_t)(packet.seq - oldseq) >= T1 && (uint16_t)(packet.seq - oldseq) < T2) 
                standard.push_back(true);
            else
                standard.push_back(false);
        }
    }    
    return;
}

Acc TestAcc(GapFilter *GapFilter, vector<Packet> &dataset, vector<bool> &standard)
{
    Acc acc;
    uint64_t size = dataset.size();
    for(uint64_t i = 0; i < size; ++i)
    {
        Packet packet = dataset[i];
        bool report_res = GapFilter->Solution(packet);
        bool stand_res = standard[i];
        if(stand_res)
        {
            if(report_res)
                acc.TP++;
            else
                acc.FN++;
        }
        else{
            if(report_res)
                acc.FP++;
            else
                acc.TN++;
        }

    }
    acc.calc();
    return acc;
}

#endif
