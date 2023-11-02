#include<bits/stdc++.h>
using namespace::std;

const int MAX = 100000 + 5;

int n;
vector<int> primes;
bool composite[MAX];

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]){
			primes.emplace_back(i);
		}
		for(int p : primes){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			if(i % p == 0) break;
		}
	}
}

int main(){
	init();
	scanf("%d", &n);
	printf("%d\n", 1 + (n > 2));
	for(int i = 2; i <= n + 1; i++){
		printf("%d%c", 1 + (int)composite[i], " \n"[i == n + 1]);
	}
	return 0;
}
