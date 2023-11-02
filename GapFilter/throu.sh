g++ -o throu throu.cpp  -fopenmp -std=c++17 -O1 -mavx -march=native
./throu $*
rm ./throu