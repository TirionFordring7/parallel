#!/bin/bash


echo "O0"
gcc -O0 -march=native lab.c -o lab.out -lm
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
echo "O1"
gcc -O1  -march=native lab.c -o lab.out -lm
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
echo "O2"
gcc -O2 -march=native lab.c -o lab.out -lm
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
echo "O3"
gcc -O3 -march=native lab.c -o lab.out -lm
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
echo "Ofast"
gcc -Ofast -march=native lab.c -o lab.out -lm
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
./lab.out
