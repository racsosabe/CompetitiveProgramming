#include<bits/stdc++.h>
using namespace::std;

const int N = 10000 + 5;

int n;
int cnt[N];
int memo[N];
int mobius[N];
bool composite[N];
vector<int> primos;

void clear(){
	memset(memo, 0, sizeof memo);
	memset(cnt, 0, sizeof cnt);
}

void init(){
	mobius[1] = 1;
	for(int i = 2; i < N; i++){
		if(not composite[i]){
			mobius[i] = -1;
			primos.emplace_back(i);
		}
		for(int p : primos){
			if(i * p >= N) break;
			composite[i * p] = true;
			mobius[i * p] = -mobius[i];
			if(i % p == 0){
				mobius[i * p] = 0;
				break;
			}
		}
	}
}

long long f(int x){
	long long num = 1;
	long long den = 1;
	for(int i = 1; i <= 4; i++){
		num *= x - i + 1;
		den *= i;
	}
	return num / den;
}

long long solve(){
	for(int i = 1; i < N; i++){
		for(int j = i; j < N; j += i) memo[i] += cnt[j];
	}
	long long ans = 0;
	for(int i = 1; i < N; i++){
		ans += f(memo[i]) * mobius[i];
	}
	return ans;
}

int main(){
	init();
	while(scanf("%d", &n) == 1){
		for(int i = 1; i <= n; i++){
			int x;
			scanf("%d", &x);
			cnt[x] += 1;
		}
		printf("%lld\n", solve());
		clear();
	}
	return 0;
}
