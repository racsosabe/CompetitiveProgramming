#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;
const long long inf = 3e18;
const int LOG = 62;

int n;
int cnt[LOG];
long long a[N];
long long costind[LOG];
long long costall[LOG];

void process(int i){
	for(int j = 0; j < LOG; j++){
		if(a[i] & (1ll << j)) cnt[j] += 1;
	}
}

long long f(long long x, int k){
	long long p = 1ll << k;
	if(x < p) return p - x;
	if(x & p) return 0;
	long long cand1 = p - x % p;
	long long cand2 = x % p + p;
	return min(cand1, cand2);
}

void get(){
	// Min cost for XOR 
	for(int j = 0; j < LOG; j++){
		if(cnt[j] & 1) continue;
		costind[j] = inf;
		for(int i = 1; i <= n; i++){
			if(a[i] & (1ll << j)) continue;
			costind[j] = min(costind[j], f(a[i], j));
		}
	}
	// Min cost for AND
	for(int j = 0; j < LOG; j++){
		for(int i = 1; i <= n; i++){
			costall[j] += f(a[i], j);
			if(costall[j] > inf) costall[j] = inf;
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", a + i);
		process(i);
	}
	get();
	long long ans = inf;
	for(int i = 0; i < LOG; i++){
		for(int j = 0; j < LOG; j++){
			if(i == j) continue;
			cout << costall[i] << " " << costind[j] << endl;
			ans = min(ans, costall[i] + costind[j]);
		}
	}
	if(n & 1){
		for(int i = 0; i < LOG; i++){
			ans = min(ans, costall[i]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
