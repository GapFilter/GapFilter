g++ -o accuracy accuracy.cpp  -fopenmp -std=c++17 -mavx -march=native
./accuracy $*
rm ./accuracy