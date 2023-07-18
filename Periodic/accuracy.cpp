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

#define MINMEM 1024
#define MAXMEM (128 * 1024)
#define DEFAULT_Lf 8
#define FEFAULT_RATIO 2 
#define SEED 149
/* readnum=-1 means loading all packets in the dataset. 
   we recommend and actually use readnum=3e6 for CAIDA dataset, -1 for others*/
#define READNUM -1 
#define Repeating_statement                                \
    GapFilter *GapFilter[64];                              \
    GapFilter[1] = new GapFilter_Straw(mem, hash_seed);    \
    GapFilter[2] = new GapFilter_SO(mem, hash_seed);       \
    GapFilter[3] = new GapFilter_AO(DEFAULT_Lf, FEFAULT_RATIO, mem, hash_seed); \
                                                           \
    for (int i = 1; i <= 3; i++)

vector<Packet> dataset;
map<FlowID,uint32_t> standard[SectionNum+2];
uint32_t TimeWindow[SectionNum+2];

void accuracyMem(char* path, int seed)
{
    uint64_t num = Load(dataset, path, READNUM);
    cout << "load packets: " << num << endl;
    srand(seed);
    int hash_seed = rand() % MAX_PRIME64;
    
    GenStandard(standard, dataset, TimeWindow);
    cout<< "gen ok" << endl;
    uint64_t mem = MINMEM;
    for (int j = 0; mem <= MAXMEM; j++, mem *= 2)
    {
        cout << "================================================="<<endl;
        cout << "Memory: "<< mem / 1024 << " KB" << endl;
        Repeating_statement
        {
            error_res res = Error_count(GapFilter[i], dataset, standard, TimeWindow);
            cout << GapFilter[i]->Name() <<": MAE = " << res.mae 
                << "; RMSE = " << res.rmse << endl;
            delete GapFilter[i];
        }
    }
    dataset.clear();
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("accuracy.cpp needs 1 parameter: input file path\n");
        return 0;
    }
    char *path = argv[1];
    accuracyMem(path, SEED);
    return 0;
}
