#!/bin/bash

g++ Gen.cpp -o gen
g++ brute.cpp -o brute
g++ Checker.cpp -o checker
veredict="Accepted"
for((i = 1; i <= 300 ; i++)); do
	./gen > int
	timeout 5 ./a.out < int > out2
	./brute < int > out1
	./checker int out2 out1 veredict.txt
	echo "Running on test $i"
	veredict=$(cat veredict.txt)
	if [ "$(cat out2)" == "" ]; then
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
