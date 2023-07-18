#ifndef _SIMD_H
#define _SIMD_H

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

static const __m512i __m512izreo =
    {0, 0, 0, 0, 0, 0, 0, 0};
static const __m256i __m256izreo =
    {0, 0, 0, 0};
static const __m128i __m128izreo =
    {0, 0};
static const __m64 __m64izreo =
    {0};

static uint16_t __attribute__((aligned(64))) num0_16[32] =
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint16_t __attribute__((aligned(64))) num5_16[32] =
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
static int16_t __attribute__((aligned(64))) numne30_16[32] =
    {-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30};    
static uint16_t __attribute__((aligned(64))) num30_16[32] =
    {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};       

static uint8_t __attribute__((aligned(64))) num0_8[64] =
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t __attribute__((aligned(64))) num5_8[64] =
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
static uint8_t __attribute__((aligned(64))) num30_8[64] =
    {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
     30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};     

static long long shuffle_8_16[16] =
    {0x0706050403020100, 0x0f0e0d0c0b0a0908, 0x0706050401000302, 0x0f0e0d0c0b0a0908,
     0x0706030201000504, 0x0f0e0d0c0b0a0908, 0x0504030201000706, 0x0f0e0d0c0b0a0908,
     0x0504030201000908, 0x0f0e0d0c0b0a0706, 0x0504030201000b0a, 0x0f0e0d0c09080706,
     0x0504030201000d0c, 0x0f0e0b0a09080706, 0x0504030201000f0e, 0x0d0c0b0a09080706};

static long long shuffle_8_16_anti[16] =
    {0x0908070605040302, 0x11100f0e0d0c0b0a, 0x0908070605040100, 0x13120f0e0d0c0b0a,
     0x0908070603020100, 0x15140f0e0d0c0b0a, 0x0908050403020100, 0x17160f0e0d0c0b0a,
     0x0706050403020100, 0x19180f0e0d0c0b0a, 0x0706050403020100, 0x1b1a0f0e0d0c0908,
     0x0706050403020100, 0x1d1c0f0e0b0a0908, 0x0706050403020100, 0x1f1e0d0c0b0a0908};

static long long shuffle_8_8[8] =
    {0x0706050403020100, 0x0706050403020001, 0x0706050403010002, 0x0706050402010003,
     0x0706050302010004, 0x0706040302010005, 0x0705040302010006, 0x0605040302010007};

static long long shuffle_8_8_anti[8] =
    {0x1007060504030201, 0x1107060504030200, 0x1207060504030100, 0x1307060504020100,
     0x1407060503020100, 0x1507060403020100, 0x1607050403020100, 0x1706050403020100};

static long long shuffle_16_16[32] =
    {
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0706050401000302,
        0x0f0e0d0c0b0a0908,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0706030201000504,
        0x0f0e0d0c0b0a0908,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0504030201000706,
        0x0f0e0d0c0b0a0908,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0504030201000908,
        0x0f0e0d0c0b0a0706,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0504030201000b0a,
        0x0f0e0d0c09080706,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0504030201000d0c,
        0x0f0e0b0a09080706,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,

        0x0504030201000f0e,
        0x0d0c0b0a09080706,
        0x0706050403020100,
        0x0f0e0d0c0b0a0908,
};

static const __m128i shuffle_8_16_half_[3] =
     {{0x0f0e0d0c0b0a0908, 0x1010101010101010},
      {0x1010101007060504, 0x1010101010101010},
      {0x1010101010100302, 0x1010101010101010}};

void Print_(__m64 x)
{
    uint32_t *p = (uint32_t *)&x;
    for (int i = 0; i < 2; i++)
        cout << *p++ << ' ';
    cout << endl;
    return;
}

void Print_(__m128i x)
{
    uint32_t *p = (uint32_t *)&x;
    for (int i = 0; i < 4; i++)
        cout << *p++ << ' ';
    cout << endl;
    return;
}

void Print_(__m256i x)
{
    uint32_t *p = (uint32_t *)&x;
    for (int i = 0; i < 8; i++)
        cout << *p++ << ' ';
    cout << endl;
    return;
}

void Print_16_(__m128i x)
{
    uint16_t *p = (uint16_t *)&x;
    for (int i = 0; i < 8; i++)
        cout << *p++ << ' ';
    cout << endl;
    return;
}
 
class SIMD_Bucket_2_16
{
public:
    uint16_t num[2];
    SIMD_Bucket_2_16()
    {
        *(int *)num = 0;
    }

    SIMD_Bucket_2_16(void *a)
    {
        *(int *)num = *(int *)a;
    }

    int Insert(uint16_t visitnum)
    {
        int i;
        int16_t diff[2];
        diff[0] = (int16_t)visitnum - (int16_t)num[0], diff[1] = (int16_t)visitnum - (int16_t)num[1];
        if(abs(diff[0]) > abs(diff[1]))
            i = 1;
        else i = 0;
        if(-30 < diff[i] && diff[i] < 30){
            if(diff[i] > 0)
                num[i] = visitnum;
            if(i == 1){
                uint16_t tmp = num[1];
                num[1] = num[0];
                num[0] = tmp;
            }
            if(diff[i] < 5) return 0;
            else return 1;
        }
        else{
            num[1] = num[0];
            num[0] = visitnum;
        }
        return 2;
    }

    void Print()
    {
        cout << num[0] << ' ' << num[1] << endl;
        return;
    }
};

class SIMD_Bucket_4_16     
{
public:
    __m64 m64_num;

    SIMD_Bucket_4_16()
    {
        memset(&m64_num, 0, sizeof(__m64));
    }

    SIMD_Bucket_4_16(void *a)
    {
        memcpy(&m64_num, a, sizeof(__m64));
    }

    int Insert(uint16_t visitnum)
    {
        int tailzero;
        int matchplace;
        int res = 0;
        __m64 m64_visitnum = (__m64)_mm_set1_pi16(visitnum);
        __m64 m64_diff = _mm_subs_pi16(m64_visitnum, m64_num);

        __m64 m64_absdiff = _mm_abs_pi16(m64_diff);
        __m64 high_part_2 = _mm_shuffle_pi16(m64_absdiff, 0b00001110);
        __m64 min_2 = _mm_min_pi16(m64_absdiff, high_part_2);
        __m64 high_part_1 = _mm_shuffle_pi16(min_2, 0b00000001);
        __m64 min_1 = _mm_min_pi16(min_2, high_part_1);
        uint16_t min_absdiff = (uint16_t)_mm_cvtsi64_si32(min_1);

        __m64 m64_mindiff = (__m64)_mm_set1_pi16(min_absdiff);                
        __m64 m64_eqdiffres = _mm_cmpeq_pi16(m64_mindiff, m64_absdiff);
        tailzero = __tzcnt_u32(_mm_movemask_pi8(m64_eqdiffres));
        matchplace = tailzero / 2;

        int16_t min_diff = int16_t(visitnum - ((uint16_t *)&m64_num)[matchplace]);
        
        if(-30 < min_diff && min_diff < 30){
            if(min_diff >= 5) 
                res = 1;
            switch (matchplace)
            {
            case 0:
                m64_num = _mm_shuffle_pi16(m64_num, 0b11100100);
                break;
            case 1:
                m64_num = _mm_shuffle_pi16(m64_num, 0b11100001);
                break;
            case 2:
                m64_num = _mm_shuffle_pi16(m64_num, 0b11010010);
                break;
            case 3:
                m64_num = _mm_shuffle_pi16(m64_num, 0b10010011);
                break;
            }
            if(min_diff > 0) 
                *(uint16_t *)&m64_num = visitnum;
            return res;
        }
        else{
            m64_num = _mm_shuffle_pi16(m64_num, 0b10010011);
            *(uint16_t *)&m64_num = visitnum;
            return 2;
        }
    }

    void Print()
    {
        uint16_t *p = (uint16_t *)&m64_num;
        for (int i = 0; i < 4; i++)
            cout << *p++ << ' ';
        cout << endl;
        return;
    }
};


class SIMD_Bucket_8_16
{
public:
    __m128i m128i_num;

    SIMD_Bucket_8_16()
    {
        memset(&m128i_num, 0, sizeof(__m128i));
    }

    SIMD_Bucket_8_16(void *a)
    {
        memcpy(&m128i_num, a, sizeof(__m128i));
    }

    int Insert(uint16_t visitnum)
    {
        int tailzero;
        int matchplace;
        int res = 0;
        __m128i m128i_visitnum;
        m128i_visitnum = (__m128i)_mm_set1_epi16(visitnum);
        __m128i m128i_diff = _mm_sub_epi16(m128i_visitnum, m128i_num);
        
        __m128i m128i_absdiff = _mm_abs_epi16(m128i_diff);
        __m128i high_part_4 = _mm_shuffle_epi8(m128i_absdiff, shuffle_8_16_half_[0]); 
        __m128i min_4 = _mm_min_epi16(m128i_absdiff, high_part_4); 
        __m128i high_part_2 = _mm_shuffle_epi8(min_4, shuffle_8_16_half_[1]); 
        __m128i min_2 = _mm_min_epi16(min_4, high_part_2); 
        __m128i high_part_1 = _mm_shuffle_epi8(min_2, shuffle_8_16_half_[2]); 
        __m128i min_1 = _mm_min_epi16(min_2, high_part_1);
        uint16_t min_absdiff = (uint16_t)_mm_cvtsi128_si64(min_1);

        __m128i m128i_mindiff = (__m128i)_mm_set1_epi16(min_absdiff);                
        __m128i m128i_eqdiffres = _mm_cmpeq_epi16(m128i_mindiff, m128i_absdiff);
        tailzero = __tzcnt_u32(_mm_movemask_epi8(m128i_eqdiffres));
        matchplace = tailzero / 2;

        int16_t min_diff = int16_t(visitnum - ((uint16_t *)&m128i_num)[matchplace]);

        if(-30 < min_diff && min_diff < 30){
            if(min_diff >= 5) res = 1;
            m128i_num = _mm_shuffle_epi8(m128i_num,
                                *((__m128i *)&shuffle_8_16[matchplace * 2]));
            if(min_diff > 0)
                *(uint16_t *)&m128i_num = visitnum;
            return res;
        }
        else{
            m128i_num = _mm_shuffle_epi8(m128i_num,
                                *((__m128i *)&shuffle_8_16[14]));
            *(uint16_t *)&m128i_num = visitnum;
            return 2;
        }
    }

    void Print()
    {
        uint16_t *p = (uint16_t *)&m128i_num;
        for (int i = 0; i < 8; i++)
            cout << *p++ << ' ';
        cout << endl;
        return;
    }
};


class SIMD_Bucket_16_16
{
public:
    __m256i m256i_num;

    SIMD_Bucket_16_16()
    {
        memset(&m256i_num, 0, sizeof(__m256i));
    }

    SIMD_Bucket_16_16(void *a)
    {
        memcpy(&m256i_num, a, sizeof(__m256i));
    }

    int Insert(uint16_t visitnum)
    {
        int tailzero;
        int matchplace;
        int res = 0;
        __m256i m256i_visitnum;
        m256i_visitnum = (__m256i)_mm256_set1_epi16(visitnum);
        __m256i m256i_diff = _mm256_sub_epi16(m256i_visitnum, m256i_num);
        __m256i m256i_absdiff = _mm256_abs_epi16(m256i_diff);
        
        __m128i high_part_8 = _mm256_extractf128_si256(m256i_absdiff, 1);
        __m128i low_part_8 = _mm256_extractf128_si256(m256i_absdiff, 0);
        __m128i min_8 = _mm_min_epi16(low_part_8, high_part_8);
        __m128i high_part_4 = _mm_shuffle_epi8(min_8, shuffle_8_16_half_[0]);
        __m128i min_4 = _mm_min_epi16(min_8, high_part_4);
        __m128i high_part_2 = _mm_shuffle_epi8(min_4, shuffle_8_16_half_[1]);
        __m128i min_2 = _mm_min_epi16(min_4, high_part_2);
        __m128i high_part_1 = _mm_shuffle_epi8(min_2, shuffle_8_16_half_[2]);
        __m128i min_1 = _mm_min_epi16(min_2, high_part_1);
        uint16_t min_absdiff = (uint16_t)_mm_cvtsi128_si64(min_1);

        __m256i m256i_mindiff = (__m256i)_mm256_set1_epi16(min_absdiff);
        __m256i m256i_eqdiffres = _mm256_cmpeq_epi16(m256i_mindiff, m256i_absdiff);
        tailzero = __tzcnt_u32(_mm256_movemask_epi8(m256i_eqdiffres));
        matchplace = tailzero / 2;

        int16_t min_diff = int16_t(visitnum - ((uint16_t *)&m256i_num)[matchplace]);

        if(-30 < min_diff && min_diff < 30){
            if(min_diff >= 5) 
                res = 1;
            if (matchplace >= 8){
                m256i_num = _mm256_shuffle_i64x2(m256i_num, m256i_num, 0b01);
                matchplace -= 8;
            }
            m256i_num = _mm256_shuffle_epi8(m256i_num,
                                        *((__m256i *)&shuffle_16_16[matchplace*4]));
            if(min_diff > 0)
                *(uint16_t *)&m256i_num = visitnum;
            return res;
        }
        else{
            m256i_num = _mm256_shuffle_i64x2(m256i_num, m256i_num, 0b01);
            m256i_num = _mm256_shuffle_epi8(m256i_num,
                                        *((__m256i *)&shuffle_16_16[28]));
            *(uint16_t *)&m256i_num = visitnum;
            return 2;
        }        
        return res;
    }
};

static const __m128i shuffle_8_16_[8][8] =
    {{{0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0706050401000302, 0x0f0e0d0c0b0a0908},
      {0x0706030201000504, 0x0f0e0d0c0b0a0908},
      {0x0504030201000706, 0x0f0e0d0c0b0a0908},
      {0x0504030201000908, 0x0f0e0d0c0b0a0706},
      {0x0504030201000b0a, 0x0f0e0d0c09080706},
      {0x0504030201000d0c, 0x0f0e0b0a09080706},
      {0x0504030201000f0e, 0x0d0c0b0a09080706}},

     {{0x0706050401000100, 0x0f0e0d0c0b0a0908},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0706030205040100, 0x0f0e0d0c0b0a0908},
      {0x0504030207060100, 0x0f0e0d0c0b0a0908},
      {0x0504030209080100, 0x0f0e0d0c0b0a0706},
      {0x050403020b0a0100, 0x0f0e0d0c09080706},
      {0x050403020d0c0100, 0x0f0e0b0a09080706},
      {0x050403020f0e0100, 0x0d0c0b0a09080706}},

     {{0x0706010003020100, 0x0f0e0d0c0b0a0908},
      {0x0706030203020100, 0x0f0e0d0c0b0a0908},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0504070603020100, 0x0f0e0d0c0b0a0908},
      {0x0504090803020100, 0x0f0e0d0c0b0a0706},
      {0x05040b0a03020100, 0x0f0e0d0c09080706},
      {0x05040d0c03020100, 0x0f0e0b0a09080706},
      {0x05040f0e03020100, 0x0d0c0b0a09080706}},

     {{0x0100050403020100, 0x0f0e0d0c0b0a0908},
      {0x0302050403020100, 0x0f0e0d0c0b0a0908},
      {0x0504050403020100, 0x0f0e0d0c0b0a0908},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0908050403020100, 0x0f0e0d0c0b0a0706},
      {0x0b0a050403020100, 0x0f0e0d0c09080706},
      {0x0d0c050403020100, 0x0f0e0b0a09080706},
      {0x0f0e050403020100, 0x0d0c0b0a09080706}},

     {{0x0706050403020100, 0x0f0e0d0c0b0a0100},
      {0x0706050403020100, 0x0f0e0d0c0b0a0302},
      {0x0706050403020100, 0x0f0e0d0c0b0a0504},
      {0x0706050403020100, 0x0f0e0d0c0b0a0706},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0706050403020100, 0x0f0e0d0c09080b0a},
      {0x0706050403020100, 0x0f0e0b0a09080d0c},
      {0x0706050403020100, 0x0d0c0b0a09080f0e}},

     {{0x0706050403020100, 0x0f0e0d0c01000908},
      {0x0706050403020100, 0x0f0e0d0c03020908},
      {0x0706050403020100, 0x0f0e0d0c05040908},
      {0x0706050403020100, 0x0f0e0d0c07060908},
      {0x0706050403020100, 0x0f0e0d0c09080908},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0706050403020100, 0x0f0e0b0a0d0c0908},
      {0x0706050403020100, 0x0d0c0b0a0f0e0908}},

     {{0x0706050403020100, 0x0f0e01000b0a0908},
      {0x0706050403020100, 0x0f0e03020b0a0908},
      {0x0706050403020100, 0x0f0e05040b0a0908},
      {0x0706050403020100, 0x0f0e07060b0a0908},
      {0x0706050403020100, 0x0f0e09080b0a0908},
      {0x0706050403020100, 0x0f0e0b0a0b0a0908},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908},
      {0x0706050403020100, 0x0d0c0f0e0b0a0908}},

     {{0x0706050403020100, 0x01000d0c0b0a0908},
      {0x0706050403020100, 0x03020d0c0b0a0908},
      {0x0706050403020100, 0x05040d0c0b0a0908},
      {0x0706050403020100, 0x07060d0c0b0a0908},
      {0x0706050403020100, 0x09080d0c0b0a0908},
      {0x0706050403020100, 0x0b0a0d0c0b0a0908},
      {0x0706050403020100, 0x0d0c0d0c0b0a0908},
      {0x0706050403020100, 0x0f0e0d0c0b0a0908}}};

class SIMD_Bucket_8_16_fpn
{
public:
    __m128i m128i_num_fp;
    __m128i m128i_num_seq;

    SIMD_Bucket_8_16_fpn()
    {
        memset(&m128i_num_fp, 0, sizeof(__m128i));
        memset(&m128i_num_seq, 0, sizeof(__m128i));
    }

    SIMD_Bucket_8_16_fpn(void *a)
    {
        memcpy(&m128i_num_seq, a, sizeof(__m128i));
    }

    int Insert(uint16_t seq, uint16_t fp, uint16_t sz) __attribute__((optimize("O1")))
    {
        uint32_t tailzero;
        uint32_t matchplace;                                               
        uint32_t res = 0;                                                  
        __m128i m128i_visitfp = (__m128i)_mm_set1_epi16(fp);               
        __m128i m128i_eqres = _mm_cmpeq_epi16(m128i_visitfp, m128i_num_fp);
        __mmask8 eqmask =  _mm_cmp_epi16_mask(m128i_visitfp, m128i_num_fp, 4);

        __m128i m128i_visitseq, m128i_diff, m128i_absdiff, high_part_4, min_4, high_part_2, min_2, high_part_1, min_1;
        uint16_t min_absdiff, min_diff; 
        __m128i m128i_mindiff, m128i_eqdiffres;
        if((uint8_t)eqmask == 0b11111111)
            goto nomatch;

        m128i_visitseq = (__m128i)_mm_set1_epi16(seq);
        m128i_diff = _mm_subs_epi16(m128i_visitseq, m128i_num_seq);
        m128i_diff = _mm_mask_set1_epi16(m128i_diff, eqmask, 0x7fff);

        m128i_absdiff = _mm_abs_epi16(m128i_diff);
        high_part_4 = _mm_shuffle_epi8(m128i_absdiff, shuffle_8_16_half_[0]);
        min_4 = _mm_min_epi16(m128i_absdiff, high_part_4);
        high_part_2 = _mm_shuffle_epi8(min_4, shuffle_8_16_half_[1]);
        min_2 = _mm_min_epi16(min_4, high_part_2);
        high_part_1 = _mm_shuffle_epi8(min_2, shuffle_8_16_half_[2]);
        min_1 = _mm_min_epi16(min_2, high_part_1);
        min_absdiff = (uint16_t)_mm_cvtsi128_si64(min_1);

        m128i_mindiff = (__m128i)_mm_set1_epi16(min_absdiff);                
        m128i_eqdiffres = _mm_cmpeq_epi16(m128i_mindiff, m128i_absdiff);
        m128i_eqdiffres = _mm_and_si128(m128i_eqdiffres, m128i_eqres);
        tailzero = __tzcnt_u32(_mm_movemask_epi8(m128i_eqdiffres));
        matchplace = tailzero / 2;

        min_diff = int16_t(seq - ((uint16_t *)&m128i_num_seq)[matchplace < 8 ? matchplace : 7]);
        if (tailzero < 32){
            if(-30 < min_diff && min_diff < 5){
                if (matchplace < sz){
                    if(seq > ((uint16_t *)&m128i_num_seq)[matchplace])
                        ((uint16_t *)&m128i_num_seq)[matchplace] = seq;
                    ((uint16_t *)&m128i_num_fp)[matchplace] = fp;
                }
                else{
                    if(seq > ((uint16_t *)&m128i_num_seq)[matchplace])
                        ((uint16_t *)&m128i_num_seq)[matchplace] = seq;
                    ((uint16_t *)&m128i_num_fp)[matchplace] = fp;
                    m128i_num_seq = _mm_shuffle_epi8(m128i_num_seq, shuffle_8_16_[sz][matchplace]);
                    m128i_num_fp = _mm_shuffle_epi8(m128i_num_fp, shuffle_8_16_[sz][matchplace]);
                }
                return 0;
            }
            else if(5 <= min_diff && min_diff < 30){
                ((uint16_t *)&m128i_num_seq)[matchplace] = seq;
                ((uint16_t *)&m128i_num_fp)[matchplace] = fp;
                m128i_num_seq = _mm_shuffle_epi8(m128i_num_seq, shuffle_8_16_[0][matchplace]);
                m128i_num_fp = _mm_shuffle_epi8(m128i_num_fp, shuffle_8_16_[0][matchplace]);
                return 1;
            }
        } 
nomatch: 
        matchplace = _tzcnt_u32(_mm_movemask_epi8(_mm_cmpeq_epi16(m128i_num_seq, __m128izreo))) / 2;
        if (matchplace < sz)
        {
            ((uint16_t *)&m128i_num_seq)[matchplace] = seq;
            ((uint16_t *)&m128i_num_fp)[matchplace] = fp;
        }
        else
        {
            if(sz > 0){
                ((uint16_t *)&m128i_num_seq)[7] = seq;
                ((uint16_t *)&m128i_num_fp)[7] = fp;
                m128i_num_seq = _mm_shuffle_epi8(m128i_num_seq, shuffle_8_16_[sz - 1][7]);
                m128i_num_fp = _mm_shuffle_epi8(m128i_num_fp, shuffle_8_16_[sz - 1][7]);
            }
            else{
                ((uint16_t *)&m128i_num_seq)[7] = seq;
                ((uint16_t *)&m128i_num_fp)[7] = fp;
                m128i_num_seq = _mm_shuffle_epi8(m128i_num_seq, shuffle_8_16_[0][7]);
                m128i_num_fp = _mm_shuffle_epi8(m128i_num_fp, shuffle_8_16_[0][7]);                
            }
        }
        return 2;
    }

    void Print()
    {
        uint16_t *p = (uint16_t *)&m128i_num_seq;
        for (int i = 0; i < 8; i++)
            cout << *p++ << ' ';
        cout << endl;
        return;
    }
};

#endif