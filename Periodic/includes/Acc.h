#ifndef _ACC_H
#define _ACC_H

#include <bits/stdc++.h>
#include "Packet.h"
#include "params.h"
#include "GapFilter.h"
using namespace std;

class error_res{
public:
    double mae = 0.0; 
    double rmse = 0.0;
    error_res(){mae = rmse = 0;}
    error_res(double mae_, double rmse_):mae(mae_),rmse(rmse_){}
    error_res(const error_res& b){
        this->mae = b.mae;
        this->rmse = b.rmse;
    }
};

class MAE{
public:
    uint32_t sum_delta;
    uint32_t total_flow;
    
    MAE(){
        sum_delta = 0;
        total_flow = 0;
    }
    double calc(){
        return (double)sum_delta/total_flow;
    }
};

class RMSE{
public:
    double sum_SE;
    uint32_t total_flow;
    
    RMSE(){
        sum_SE = 0.0;
        total_flow = 0;
    }
    double calc(){
        return sqrt((double)sum_SE/total_flow);
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

void GenStandard(map<FlowID,uint32_t> standard[], vector<Packet> &dataset, uint32_t TimeWindow[]){
    map<FlowID, uint16_t> mp;
    uint64_t cnt = 0;
    mp.clear();
        
    uint64_t total = dataset.size();
    uint32_t ed = dataset[total-1].time;
    uint32_t interval = ed /SectionNum;
    uint32_t section_ed = 0;
    int TimeWindowCount = 0;

    for(int i = 1; i <= SectionNum; i++){
        if(i < SectionNum)
            TimeWindow[i] = interval*i;
        else
            TimeWindow[i] = 0xffffffffu;
    }

    for (uint64_t i = 0; i < total; ++i)
    {
        Packet packet = dataset[i];

        if (packet.time >= section_ed || i == total -1){
            TimeWindowCount ++;
            standard[TimeWindowCount].clear();
            if(TimeWindowCount < SectionNum)
                section_ed += interval;
            else
                section_ed = 0xffffffffu;
        }

        bool res = false;
        uint16_t oldseq = 0;
        if (!mp.count(packet.id))
            mp[packet.id] = packet.seq;
        else
        {
            oldseq = mp[packet.id];
            if (packet.seq > oldseq || oldseq - packet.seq >= THRES)
                mp[packet.id] = packet.seq;
            if ((uint16_t)(packet.seq - oldseq) >= T1 && (uint16_t)(packet.seq - oldseq) < T2) 
                res = true;
        }

        if(res){
            if(standard[TimeWindowCount].count(packet.id))
                ++ standard[TimeWindowCount][packet.id];
            else standard[TimeWindowCount][packet.id] = 1;            
        }
    }
}

error_res Error_count(GapFilter *GapFilter, vector<Packet> &dataset, 
                        map<FlowID,uint32_t> standard[], uint32_t TimeWindow[])
{
    set<FlowID> flow_num;
    flow_num.clear();
 
    double aver_mae = 0.0;
    double aver_rmse = 0.0;

    map<FlowID,uint32_t> blacklist_res;
    blacklist_res.clear();
    uint32_t total = dataset.size();

    int section_st_i = 0;
    int TimeWindowCount = 1;
    uint32_t section_ed = TimeWindow[1];

    for (uint32_t i = 0; i <= total; ++i)
    {
        Packet packet;
        if(i != total) packet = dataset[i];

        if (i == total || packet.time >= section_ed){
            if(i != 0)
            {
                // printf("TimeWindow=%d,i=%d,section_st_i=%d,section_ed=%u\n",
                //        TimeWindowCount,i,section_st_i,section_ed);
                TimeWindowCount ++;
                section_ed = TimeWindow[TimeWindowCount];
                
                flow_num.clear();
                for(int j = section_st_i; j < i; j ++){
                    Packet packet = dataset[j];
                    flow_num.insert(packet.id);
                }
                section_st_i = i;
                //printf("flow_num=%lu\n", flow_num.size());

                blacklist_res.clear();
                GapFilter->Report(blacklist_res);
                MAE mae;
                RMSE rmse;
                for(auto [flowID, freq] : standard[TimeWindowCount-1])
                {
                    if(!blacklist_res.count(flowID)) blacklist_res[flowID] = 0;
                    mae.sum_delta += abs((int)freq - (int)blacklist_res[flowID]);
                    rmse.sum_SE += ((int)freq - (int)blacklist_res[flowID])*((int)freq - (int)blacklist_res[flowID]);
                    blacklist_res[flowID] = 0;
                }
                for(auto [flowID, freq] : blacklist_res)
                {
                    if(freq != 0){
                        mae.sum_delta += freq;
                        rmse.sum_SE += freq*freq;
                    }
                }
                mae.total_flow = flow_num.size();
                rmse.total_flow = flow_num.size();
                flow_num.clear();
                aver_mae += mae.calc();
                aver_rmse += rmse.calc();
                blacklist_res.clear();
            }
            if(i == total) break;
        }
        GapFilter->Solution(packet);
    }

    aver_mae /= SectionNum;
    aver_rmse /= SectionNum;
    return error_res(aver_mae, aver_rmse);
}

#endif