#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "includes/Acc.h"
#include "includes/Packet.h"
#include "includes/GapFilter_Straw.h"
#include "includes/GapFilter_SO.h" 
#include "includes/GapFilter_AO.h"
using namespace std;

#define MINMEM (30 * 1024)
#define MAXMEM  (210 * 1024)
#define INTERVAL (30 * 1024)
#define DEFAULT_Lf 8
#define FEFAULT_RATIO 2 
#define SEED 149
#define READNUM -1 
#define Repeating_statement                                \
    GapFilter *GapFilter[64];                              \
    GapFilter[1] = new GapFilter_Straw(mem, hash_seed);    \
    GapFilter[2] = new GapFilter_SO(mem, hash_seed);       \
    GapFilter[3] = new GapFilter_AO(DEFAULT_Lf, FEFAULT_RATIO, mem, hash_seed); \
                                                           \
    for (int i = 1; i <= 3; i++)

const char csvheader[1024] = 
    "Mem\
,GapFilter_Straw\
,GapFilter_SO4\
,GapFilter_AO\n";

vector<Packet> dataset;

void Throughput(char* path, int seed)
{
    uint64_t num = Load(dataset, path, READNUM);
    cout << "load packets: " << num << endl;
    srand(seed);
    int hash_seed = rand() % MAX_PRIME64;

    clock_t start, finish;
    uint64_t totsize = dataset.size();
    ofstream Tout("./Throu.csv", ios::trunc | ios::out);
    Tout << csvheader;
    for (uint64_t mem = MINMEM; mem <= MAXMEM; mem += INTERVAL)
    {
        Tout << mem /1024;
        Repeating_statement
        {
            start = clock();
            for (uint64_t k = 0; k < totsize; k++)
                GapFilter[i]->Solution(dataset[k]);
            finish = clock();
            delete GapFilter[i];
            Tout << ',' << (double)totsize / 1e6 / (((double)finish - start) / CLOCKS_PER_SEC);
        }
        Tout << endl;
    }
    dataset.clear();
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("throu.cpp needs 1 parameter: input file path\n");
        return 0;
    }
    char *path = argv[1];
    Throughput(path, SEED);

    return 0;
}
