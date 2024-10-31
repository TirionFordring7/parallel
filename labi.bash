#!/bin/bash


echo "O0"
gcc -O0 -mavx -march=native labi.c -o labi.out -lm
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
echo "O1"
gcc -O1 -mavx -march=native labi.c -o labi.out -lm
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
echo "O2"
gcc -O2 -mavx -march=native labi.c -o labi.out -lm
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
echo "O3"
gcc -O3 -mavx -march=native labi.c -o labi.out -lm
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
echo "Ofast"
gcc -Ofast -mavx -march=native labi.c -o labi.out -lm
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
./labi.out
