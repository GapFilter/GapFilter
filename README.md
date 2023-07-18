# GapFilter

## parser

We implement our GapFilter-SO, GapFilter-AO and Straw-man solution in C++ on a CPU platform. 

In parser.sh and parser.cpp, we use a typical method of parsing a .pcap source file (and times file for timestamp, if exist) to create an output file in which each item follows <FID, SEQ, TIMESTAMP> format, preparing for our subsequent experiments.

## Real-time

acc.sh and accuracy.cpp are used for conducting experiments and comparing the accuracy (F1, PR, RR) of the three solutions on different memory size.

throu.sh and throu.cpp are used for comparing the processing speed of the three solutions.

In test.sh, we provided an simple way of adjusting the parameters of GapFilter-AO and observing its accuarcy. The meaning of some of the options are provided in the chart below: 

| Argument name      | meaning                                                               |
|--------------------|-----------------------------------------------------------------------|
| -f / --file        | directory to where you store the dataset file processed by parser.sh                             |
| -m / --mem       | memory size(KB) for our GapFilter solution (default 16KB)                                              |
| -l / --length       | the length(bits) of fingerprint in GapFilter-AO within [0,16] (default 8bits)                                           |
| -r / --ratio       | the number of suspect cell in  GapFilter-AO within [0,8], while the ratio of suspect/civilian varies from 0:8 to 8:0 (default 2:6)                           |
| -s / --seed        | the hash seed for init                                                   |

Above experiments all use the output file created in Parser as input.

## Periodic 

acc.sh and accuracy.cpp are used for conducting experiments and comparing the accuracy (MAE, RMSE) of the three solutions on different memory size.

