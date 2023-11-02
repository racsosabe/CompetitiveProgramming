/*
ID: Victor Racso Galvan Oyola (racso_g1)
LANG: C++
TASK: ride
*/

#include<bits/stdc++.h>
using namespace::std;

void setIO(string name){
	string inputname = name + ".in";
	string outputname = name + ".out";
	freopen(inputname.c_str(), "r", stdin);
	freopen(outputname.c_str(), "w", stdout);
}

const int N = 10;

char s[N];

int get_val(){
	int res = 1;
	for(int i = 0; s[i]; i++){
		res *= s[i] - 'A' + 1;
		res %=  47;
	}
	return res;
}

int main(){
	setIO("ride");
	scanf("%s", s);
	int a = get_val();
	scanf("%s", s);
	int b = get_val();
	puts(a == b ? "GO" : "STAY");
	return 0;
}
