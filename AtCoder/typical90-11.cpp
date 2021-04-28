#include<bits/stdc++.h>
using namespace::std;

const int N = 5000 + 5;

int n;
int c[N];
int v[N];
int d[N];
long long memo[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d %d", d + i, c + i, v + i);
	}
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return d[i] < d[j];
	});
	for(int i : p){
		for(int ending = d[i]; ending >= c[i]; ending--){
			long long cand = v[i] + memo[ending - c[i]];
			if(memo[ending] < cand) memo[ending] = cand;
		}
		for(int i = 1; i < N; i++) memo[i] = max(memo[i], memo[i - 1]);
	}
	printf("%lld\n", memo[N - 1]);
	return 0;
}
