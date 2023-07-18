#ifndef _PARAMS_H
#define _PARAMS_H

#define FLOWID_LEN 13

#define testcycles 5

#define LOSS_PROB 0.1

#define SectionNum 20

#define STRAWCELLSIZE (FLOWID_LEN+sizeof(Seq)+sizeof(Pointer))

#define BASESIZE ((double)2/3)

#define T1 ((uint16_t)5u)

#define T2 ((uint16_t)30u)

#define THRES 100

#define AOBUCKETSIZE 8

typedef uint64_t Pointer;

#endif