#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>
#include "includes/Acc.h"
#include "includes/Packet.h"
#include "includes/GapFilter_Straw.h"
#include "includes/GapFilter_SO.h" 
#include "includes/GapFilter_AO.h"
using namespace std;

#define MEM (16 * 1024)
#define DEFAULT_Lf 8
#define FEFAULT_RATIO 2 
#define SEED 149
#define READNUM -1 
vector<Packet> dataset;
vector<bool> standard;

char* path;
uint64_t mem = MEM;
uint32_t lf = DEFAULT_Lf;
uint32_t sus = FEFAULT_RATIO;
int seed = SEED;

void Test()
{
    uint64_t num = Load(dataset, path, READNUM);
    cout << "load packets: " << num << endl;
    srand(seed);
    int hash_seed = rand() % MAX_PRIME64;
    
    GenStandard(standard, dataset);
    
    GapFilter* GapFilter = new GapFilter_AO(lf, sus, mem, hash_seed);
    Acc acc = TestAcc(GapFilter, dataset, standard);
    
    cout << "GapFilter_AO parameters:\n";
    cout << "memory = " << mem/1024 << " KB\n";
    cout << "fingerprint length = "<< lf << "bits\n";
    cout << "suspect/civilian ratio = "<< sus <<" : "<< AOBUCKETSIZE - sus <<"\n";
    cout << "\n";
    cout << "Result: TP = " << acc.TP << "; FP = " << acc.FP 
        << "; TN = " << acc.TN << "; FN = " << acc.FN << "\n";
    cout << "Accuray: F1 = " << acc.F1 << "; RR = " << acc.RR << "; PR = " << acc.PR << "\n";
    delete GapFilter;
    dataset.clear();
    standard.clear();
}

void getParam(int argc, char *argv[])
{
    int opt;
    int digit_optind = 0;
    int option_index = 0;
    const char *optstring = "f:m:l:r:s:";
    static struct option long_options[] = {
        {"file", required_argument, NULL, 'f'},
        {"mem",  required_argument,  NULL, 'm'},
        {"length", required_argument, NULL, 'l'},
        {"ratio", required_argument, NULL, 'r'},
        {"seed", required_argument, NULL, 's'},
        {0, 0, 0, 0}
    };

    while ( (opt = getopt_long(argc, argv, optstring,
                            long_options, &option_index)) != -1) {
        switch(opt){
            case 'f': 
                path = optarg; break;
            case 'm': 
                mem = atoi(optarg)*1024; break;
            case 'l':
                lf =  atoi(optarg); break;
            case 'r':
                sus = atoi(optarg); break;
            case 's':
                seed = atoi(optarg); break;
            default:
                printf("wrong parameter!\n");
                exit(0);
        }
        if(lf < 0 || lf > 16){
            printf("Usage: length of fingerprint should be an integer in [0,16].\n");
            exit(0);
        }
        if(sus < 0 || sus > 8){
            printf("Usage: ratio should be an integer in [0,8].\n\
                ,for it is the number of suspect cell in AO bucket with 8 cells");
            exit(0);
        }
        if(mem < 0){
            printf("Usage: memory size(KB) should be a positive number.\n");
            exit(0);    
        }
    }
}

int main(int argc, char *argv[])
{
    getParam(argc, argv);
    Test();
    return 0;
}
