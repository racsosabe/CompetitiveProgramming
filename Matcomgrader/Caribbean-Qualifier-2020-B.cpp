#include<bits/stdc++.h>
using namespace::std;

const int MAX = 1000000 + 5;
const int N = 100000 + 5;

int n;
int cnt[MAX];
int memo[MAX];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		cnt[x] += 1;
	}
	for(int i = 1; i < MAX; i++){
		for(int j = i; j < MAX; j += i) memo[i] += cnt[j];
	}
	long long ans = 0;
	for(int i = 1; i < MAX; i++){
		if(memo[i] > 1) ans = max(ans, 1ll * i * memo[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
