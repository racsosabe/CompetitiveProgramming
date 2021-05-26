#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int a[N];
int prefix[N];
int suffix[N];

int solve(){
	prefix[1] = 1;
	prefix[2] = 2;
	for(int i = 3; i <= n; i++){
		prefix[i] = 1;
		if(a[i] - a[i - 1] == a[i - 1] - a[i - 2]) prefix[i] += prefix[i - 1];
		else prefix[i] += 1;
	}
	suffix[n + 1] = 0;
	suffix[n] = 1;
	suffix[n - 1] = 2;
	for(int i = n - 2; i >= 1; i--){
		suffix[i] = 1;
		if(a[i + 1] - a[i] == a[i + 2] - a[i + 1]) suffix[i] += suffix[i + 1];
		else suffix[i] += 1;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){
		ans = max({ans, prefix[i], suffix[i]});
		ans = max({ans, 1 + prefix[i - 1], 1 + suffix[i + 1]});
		if(1 == i or i == n) continue;
		if((a[i - 1] + a[i + 1]) & 1) continue;
		int x = (a[i - 1] + a[i + 1]) / 2;
		int cand = 1;
		if(i > 2 and x - a[i - 1] == a[i - 1] - a[i - 2]) cand += prefix[i - 1];
		else cand += 1;
		if(i + 2 <= n and a[i + 1] - x == a[i + 2] - a[i + 1]) cand += suffix[i + 1];
		else cand += 1;
		ans = max(ans, cand);
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	for(int caso = 1; caso <= t; caso++){
		printf("Case #%d: ", caso);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d", a + i);
		}
		printf("%d\n", solve());
	}
	return 0;
}

