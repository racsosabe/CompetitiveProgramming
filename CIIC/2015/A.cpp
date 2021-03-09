#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Just notice that if you can eat X chocolates each day, then you can eat (X - 1)

	- The former observation is enough to use binary search the answer.

	- Complexity: O(nlogMAX).

*/

const int N = 100000 + 5;

int n;
int c[N];

bool can(int wants){
	long long cur = 0LL;
	for(int i = 1; i <= n; i++){
		cur += c[i];
		cur -= wants;
		if(cur < 0) return false;
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", c + i);
	int lo = 0, hi = 1000000000;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(can(mi)) lo = mi;
		else hi = mi - 1;
	}
	printf("%d\n", lo);
	return 0;
}
