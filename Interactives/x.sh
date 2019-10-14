#!/bin/bash

if [ $# -eq 1 ]; then
	g++ "$1.cpp"
	./Test.sh
else
	echo "No hay la cantidad correcta de parametros"
fi
