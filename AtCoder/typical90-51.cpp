#include<bits/stdc++.h>
using namespace::std;

const int N = 40 + 5;

int n;
int k;
long long p;
long long a[2][N];
vector<long long> values[2][N];

void process(int id, int len){
	vector<long long> sum(1 << len, 0ll);
	values[id][0].emplace_back(0);
	for(int mask = 1; mask < (1 << len); mask++){
		int pos = __builtin_ctz(mask);
		sum[mask] = sum[mask & (mask - 1)] + a[id][pos];
		values[id][__builtin_popcount(mask)].emplace_back(sum[mask]);
	}
	for(int i = 0; i <= len; i++){
		sort(values[id][i].begin(), values[id][i].end());
	}
}

long long solve(int len){
	long long ans = 0;
	for(int s1 = 0; s1 <= len and s1 <= k; s1++){
		int s2 = k - s1;
		int pos = values[1][s2].size() - 1;
		for(auto x : values[0][s1]){
			while(pos >= 0 and values[1][s2][pos] + x > p){
				pos -= 1;
			}
			ans += pos + 1;
		}
	}
	return ans;
}

int main(){
	scanf("%d %d %lld", &n, &k, &p);
	int len = n / 2;
	for(int i = 0; i < n; i++){
		if(i < len) scanf("%lld", &a[0][i]);
		else scanf("%lld", &a[1][i - len]);
	}
	for(int i = 0; i < 2; i++){
		process(i, i == 0 ? len : n - len);
	}
	printf("%lld\n", solve(len));
	return 0;
}
