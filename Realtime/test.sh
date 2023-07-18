g++ -o test controller.cpp  -fopenmp -std=c++17 -mavx -march=native
./test $* # --file [path] --mem 64 --length 8 --ratio 2 --seed 149
rm ./test