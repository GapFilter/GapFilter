# GapFilter

We implement our GapFilter-SO, GapFilter-AO, and Straw-man solutions in C++ on a CPU platform. 

## parser

In parser.sh and parser.cpp, we use a typical method of parsing the .pcap source file (and the time file for packet's timestamp, if exist) to create an output file in which each item follows the <FID, SEQ, TIMESTAMP> format, preparing for our subsequent experiments.

## GapFilter

We provide the codes of GapFilter-SO, GapFilter-AO, and Straw-man solutions. The file with "GapFilter_XX_woSIMD" in its name is the corresponding implementation without SIMD acceleration, while "GapFilter_XX" uses acceleration technology. In simd.h and wosimd.h, we provide more implementations in variable bucket sizes and flexible parameters.

acc.sh and accuracy.cpp are used for conducting experiments and comparing the accuracy (F1, PR, and RR) of the three solutions on different memory sizes.

throu.sh and throu.cpp are used for comparing the processing speeds of the three solutions.

In test.sh, we provide an simple way of adjusting the parameters of GapFilter-AO and observing its accuracy. The meaning of some of the options are provided in the chart below: 

| Option name      | meaning                                                               |
|--------------------|-----------------------------------------------------------------------|
| -f / --file        | directory to where you store the dataset file processed by parser.sh                             |
| -m / --mem       | memory size(KB) for our GapFilter solution (default 16KB)                                              |
| -l / --length       | the length(bits) of fingerprint in GapFilter-AO within [0,16] (default 8bits)                                           |
| -r / --ratio       | the number of suspect cell in  GapFilter-AO within [0,8], adjusting the ratio of suspect/civilian vary from 0:8 to 8:0 (default 2:6)                           |
| -s / --seed        | the hash seed                                                   |

## Dataset

We provide the following links to download datasets in .pcap format for testing, which are also used for accuracy tests in our paper.

CAIDA(equinix-nyc.dirA.20180315-130000.UTC.anon.pcap): https://data.caida.org/datasets/passive-2018

MAWI: http://mawi.nezu.wide.ad.jp/mawi/samplepoint-F/2023/202305131400.pcap.gz

MACCDC(2012): https://www.netresec.com/?page=MACCDC

IMC: https://pages.cs.wisc.edu/~tbenson/IMC_DATA/univ1_trace.tgz

### References
BOBHash (http://burtleburtle.net/bob/hash/evahash.html) is used as the hash function in the code.
