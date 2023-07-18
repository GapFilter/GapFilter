#ifndef _PACKET_H
#define _PACKET_H

#include <bits/stdc++.h>
#include "params.h"
using namespace std;
typedef uint16_t Seq;

class FlowID
{
public:
    uint8_t data[FLOWID_LEN];
    
    FlowID(){ memset(data, 0, FLOWID_LEN); }
    FlowID(const char* t){
        for (int i = 0; i < FLOWID_LEN; i++)
            data[i] = t[i];
    }
    FlowID(const FlowID& t){
        for (int i = 0; i < FLOWID_LEN; i++)
            data[i] = t.data[i];
    }

    uint32_t SrcIP() const{
        return *((uint32_t*)data);
    }

    uint32_t DstIP() const{
        return *((uint32_t*)(data + 4));
    }

    uint16_t SrcPort() const{
        return *((uint16_t*)(data + 8));
    }

    uint16_t DstPort() const{
        return *((uint16_t*)(data + 10));
    }

    uint8_t Protocal() const{
        return data[FLOWID_LEN-1];
    }

    inline bool empty() const{
        for (int i = 0; i < FLOWID_LEN; i++)
            if (data[i])
                return false;
        return true;
    }

    bool operator<(const FlowID &t) const {
        for (int i = 0; i < FLOWID_LEN; i++) {
            if (data[i] != t.data[i])
                return data[i] < t.data[i];
        }
        return 0;
    }

    FlowID& operator=(const FlowID& t){
        for (int i = 0; i < FLOWID_LEN; i++)
            data[i] = t.data[i];
        return *this;
    }

};

bool operator == (const FlowID& a, const FlowID& b){
    return memcmp(a.data, b.data, FLOWID_LEN) == 0;
}

bool operator == (const FlowID& a, const uint8_t* b){
    return memcmp(a.data, b, FLOWID_LEN) == 0;
}

ostream& operator<<(ostream &out, const FlowID &t) {
    out << (uint32_t)t.data[0];
    for (int i = 1; i < FLOWID_LEN; i++)
        out << ' ' << (uint32_t)t.data[i];
    return out;
}

istream& operator>>(istream &in, FlowID &t) {
    uint32_t tmp;
    for (int i = 0; i < FLOWID_LEN; i++){
        in >> tmp;
        t.data[i]=(uint8_t)tmp;
    }
    return in;
}

class Packet
{
public:
    FlowID id;
    uint32_t time;
    uint16_t seq;
    Packet() {}
    Packet(FlowID id_, uint32_t time_, uint16_t seq_) : id(id_), time(time_), seq(seq_) {}
    void PrintInfo()
    {
        cout << id <<" ";
        printf("time = %u, seq = %u\n", time, seq);
    }
};

#endif