#include<bits/stdc++.h>
using namespace::std;

const int N = 750 + 5;

int n;
int q;
int a[N];
long long mini[N];
long long prefix[N];

int f(long long b){
	priority_queue<int> Q;
	int ans = 0;
	for(int i = 1; i <= n; i++){
		b += a[i];
		Q.emplace(-a[i]);
		while(b < 0){
			int take = Q.top();
			Q.pop();
			ans += 1;
			b += take;
		}
	}
	return ans;
}

void preprocess(){
	long long last = 1e18;
	while(last > 0){
		int want = f(last);
		long long lo = 0, hi = last;
		while(lo < hi){
			long long mi = lo + (hi - lo) / 2;
			if(f(mi) > want) lo = mi + 1;
			else hi = mi;
		}
		mini[want] = lo;
		last = lo - 1;
	}	
}

int solve(long long b){
	for(int i = 0; i <= n; i++){
		if(mini[i] <= b) return i;
	}
	return -1;
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	preprocess();
	while(q--){
		long long b;
		scanf("%lld", &b);
		printf("%d\n", solve(b));
	}
	return 0;
}
