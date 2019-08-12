#!/bin/bash

g++ Gen.cpp -o gen
g++ brute.cpp -o brute
g++ Checker.cpp -o checker
veredict="Accepted"
for((i=0; i < 1000 ; i++)); do
	./gen > int
	timeout 3 ./a.out < int > out
	./brute < int > out2
	./checker int out out2 veredict.txt
	echo "Running on test $i"
	veredict=$(cat veredict.txt)
	if [ "$(cat out)" == "" ]; then
		veredict="Time Limit Exceeded"
		testcase="$i"
	fi
	if [ "$veredict" != "Accepted" ]; then
		break
	fi
done
if [ "$veredict" == "Accepted" ];then
	echo $veredict
else
	echo "$veredict on test $testcase"
	cat int
fi
