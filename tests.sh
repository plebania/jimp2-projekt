#!/bin/sh
#ARGUMENTY


echo Test kopiec 1:
./bin/graph test --kopiec 10 2.0 5.0
echo Test kopiec 2:
./bin/graph test --kopiec 10 2.0 2.0
echo Test kopiec 3:
./bin/graph test --kopiec 10 -1.0 1.0
echo Test kopiec 4:
./bin/graph test --kopiec 10 -2.0 -1.0
echo Test kopiec 5:
./bin/graph test --kopiec 10 -2.0 0.0


echo Test kolejka 1:
./bin/graph test --kolejka 100
#./bin/graph make dane/plik_wyjscowy 5 5 1 10
#./bin/graph check dane/dane1
#./bin/graph path dane/dane1 1 1 2 2