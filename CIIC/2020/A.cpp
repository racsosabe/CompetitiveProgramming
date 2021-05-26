#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int MAX = 2000 + 5;
const long long inf = 1e18;

int n;
int m;
int P[N];
int F[N];
int T[N];
long long memo[MAX];

long long solve(){
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return 1ll * T[i] * F[j] < 1ll * T[j] * F[i];
	});
	for(int i = 1; i <= m; i++) memo[i] = -inf;
	for(int i : p){
		for(int timer = m; timer >= T[i]; timer--){
			memo[timer] = max(memo[timer], memo[timer - T[i]] + P[i] - 1ll * timer * F[i]);
		}
	}
	return *max_element(memo, memo + MAX);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d %d %d", P + i, F + i, T + i);
	printf("%lld\n", solve());
	return 0;
}
