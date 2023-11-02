#include<bits/stdc++.h>
using namespace::std;

const int MAX = 10000000 + 5;

int n;
int k;
int cnt[MAX];
vector<int> primes;
bool composite[MAX];

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]){
			cnt[i] = 1;
			primes.emplace_back(i);
		}
		for(int p : primes){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			cnt[i * p] = cnt[i] + 1;
			if(i % p == 0){
				cnt[i * p] = cnt[i];
				break;
			}
		}
	}
}

int main(){
	init();
	scanf("%d %d", &n, &k);
	int ans = 0;
	for(int i = 1; i <= n; i++) ans += (cnt[i] >= k);
	printf("%d\n", ans);
	return 0;
}
