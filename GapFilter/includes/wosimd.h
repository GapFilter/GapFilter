#ifndef _WOSIMD_H
#define _WOSIMD_H

#include <bits/stdc++.h>
using namespace std;

class SO_woSIMD_Bucket_4_16     
{
public:
    uint16_t num[4];

    SO_woSIMD_Bucket_4_16()
    {
        memset(num, 0, sizeof(num));
    }

    int Insert(uint16_t visitnum)
    {
        int res = 0;
        int matchplace;
        int32_t min_diff = 0x7ffffff;
        for(int i = 0; i < 4; i++){
            int16_t delta = (int16_t)visitnum - (int16_t)num[i];
            if(abs(delta) < abs(min_diff)){
                min_diff = delta;
                matchplace = i;
            }
        }

        if(int16_t(-30) < min_diff && min_diff < 30){
            uint16_t insertnum = num[matchplace];
            if(min_diff > 0){
                insertnum = visitnum;
                if(min_diff >= 5) 
                    res = 1;
            }
            switch (matchplace){
            case 0: break;
            case 1:
                num[1] = num[0];
                break;
            case 2:
                num[2] = num[1]; num[1] = num[0];
                break;
            case 3:
                num[3] = num[2]; num[2] = num[1]; num[1] = num[0];
                break;
            }
            num[0] = insertnum;
            return res;
        }
        else{
            num[3] = num[2]; num[2] = num[1]; num[1] = num[0];
            num[0] = visitnum;
            return 2;
        }
    }
};


class woSIMD_Bucket_8_16_fpn
{
public: 
    uint16_t sz;
    uint16_t num_fp[8];
    uint16_t num_seq[8];

    woSIMD_Bucket_8_16_fpn(uint16_t sz_)
    {
        sz = sz_;
        memset(num_fp, 0, sizeof(num_fp));
        memset(num_seq, 0, sizeof(num_seq));
    }

    int Insert(uint16_t seq, uint16_t fp)
    {
        int matchplace = -1;
        int32_t min_diff = 0x7ffffff;
        for(int i = 0; i < 8; i++){
            if(num_fp[i] == fp){
                int16_t delta = (int16_t)seq - (int16_t)num_seq[i];
                if(abs(delta) < abs(min_diff)){
                    min_diff = delta;
                    matchplace = i;
                }
            }
        }
        
        if(int16_t(-30) < min_diff && min_diff < 30){
            if(min_diff < 5){
                if(min_diff > 0)
                    num_seq[matchplace] = seq;
                if(matchplace >= sz){
                    uint16_t tmp_fp = num_fp[matchplace], 
                            tmp_seq = num_seq[matchplace];
                    for(int i = matchplace; i > sz; i--){
                        num_fp[i] = num_fp[i-1];
                        num_seq[i] = num_seq[i-1];
                    }
                    num_fp[sz] = tmp_fp;
                    num_seq[sz] = tmp_seq;
                }
                return 0;
            }
            else{
                for(int i = 7; i > 0; i--){
                    num_fp[i] = num_fp[i-1];
                    num_seq[i] = num_seq[i-1];
                }
                num_fp[0] = fp;
                num_seq[0] = seq;
                return 1;
            }
        }
        else{
            int emptyplace = 7; 
            for(int i = 0; i < 8; i++){
                if(num_fp[i] == 0 && num_seq[i] == 0){
                    emptyplace = i;
                    break;
                }
            }

            if(emptyplace < sz){
                num_fp[emptyplace] = fp;
                num_seq[emptyplace] = seq;
            }
            else{
                for(int i = emptyplace; i > sz; i--){
                    num_fp[i] = num_fp[i-1];
                    num_seq[i] = num_seq[i-1];
                }
                num_fp[sz] = fp;
                num_seq[sz] = seq;
            }
            return 2;
        }
        return 2;
    }
};

class SO_woSIMD_Bucket_8_16
{
public: 
    uint16_t num[8];

    SO_woSIMD_Bucket_8_16()
    {
        memset(num, 0, sizeof(num));
    }

    int Insert(uint16_t visitnum)
    {
        int res = 0;
        int matchplace;
        int32_t min_diff = 0x7ffffff;
        for(int i = 0; i < 8; i++){
            int16_t delta = (int16_t)visitnum - (int16_t)num[i];
            if(abs(delta) < abs(min_diff)){
                min_diff = delta;
                matchplace = i;
            }
        }

        if(int16_t(-30) < min_diff && min_diff < 30){
            uint16_t insertnum = num[matchplace];
            if(min_diff > 0){
                insertnum = visitnum;
                if(min_diff >= 5) 
                    res = 1;
            }
            for(int i=matchplace;i>0;i--)
            {
                num[i] = num[i-1];
            }
            num[0] = insertnum;
            return res;
        }
        else{
            for(int i=7;i>0;i--)
            {
                num[i] = num[i-1];
            }
            num[0] = visitnum;
            return 2;
        }
    }
};

class SO_woSIMD_Bucket_16_16
{
public: 
    uint16_t num[16];

    SO_woSIMD_Bucket_16_16()
    {
        memset(num, 0, sizeof(num));
    }

    int Insert(uint16_t visitnum)
    {
        int res = 0;
        int matchplace;
        int32_t min_diff = 0x7ffffff;
        for(int i = 0; i < 16; i++){
            int16_t delta = (int16_t)visitnum - (int16_t)num[i];
            if(abs(delta) < abs(min_diff)){
                min_diff = delta;
                matchplace = i;
            }
        }

        if(int16_t(-30) < min_diff && min_diff < 30){
            uint16_t insertnum = num[matchplace];
            if(min_diff > 0){
                insertnum = visitnum;
                if(min_diff >= 5) 
                    res = 1;
            }
            for(int i=matchplace;i>0;i--)
            {
                num[i] = num[i-1];
            }
            num[0] = insertnum;
            return res;
        }
        else{
            for(int i=15;i>0;i--)
            {
                num[i] = num[i-1];
            }
            num[0] = visitnum;
            return 2;
        }
    }
};

class woSIMD_Bucket_16_16_fpn
{
public: 
    uint16_t sz;
    uint16_t num_fp[16];  
    uint16_t num_seq[16]; 

    woSIMD_Bucket_16_16_fpn(uint16_t sz_)
    {
        sz = sz_;
        memset(num_fp, 0, sizeof(num_fp));
        memset(num_seq, 0, sizeof(num_seq));
    }

    int Insert(uint16_t seq, uint16_t fp)
    {
        int matchplace = -1;
        int32_t min_diff = 0x7ffffff;
        for(int i = 0; i < 16; i++){
            if(num_fp[i] == fp){
                int16_t delta = (int16_t)seq - (int16_t)num_seq[i];
                if(abs(delta) < abs(min_diff)){
                    min_diff = delta;
                    matchplace = i;
                }
            }
        }
        
        if(int16_t(-30) < min_diff && min_diff < 30){
            if(min_diff < 5){
                if(min_diff > 0)
                    num_seq[matchplace] = seq;
                if(matchplace >= sz){
                    uint16_t tmp_fp = num_fp[matchplace], 
                            tmp_seq = num_seq[matchplace];
                    for(int i = matchplace; i > sz; i--){
                        num_fp[i] = num_fp[i-1];
                        num_seq[i] = num_seq[i-1];
                    }
                    num_fp[sz] = tmp_fp;
                    num_seq[sz] = tmp_seq;
                }
                return 0;
            }
            else{
                for(int i = 15; i > 0; i--){
                    num_fp[i] = num_fp[i-1];
                    num_seq[i] = num_seq[i-1];
                }
                num_fp[0] = fp;
                num_seq[0] = seq;
                return 1;
            }
        }
        else{
            int emptyplace = 15; 
            for(int i = 0; i < 16; i++){
                if(num_fp[i] == 0 && num_seq[i] == 0){
                    emptyplace = i;
                    break;
                }
            }

            if(emptyplace < sz){
                num_fp[emptyplace] = fp;
                num_seq[emptyplace] = seq;
            }
            else{
                for(int i = emptyplace; i > sz; i--){
                    num_fp[i] = num_fp[i-1];
                    num_seq[i] = num_seq[i-1];
                }
                num_fp[sz] = fp;
                num_seq[sz] = seq;
            }
            return 2;
        }
        return 2;
    }
};

#endif