#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

int n;
int M;
int len;
int at, sz;
int pos = 0;
long long memo[N];
pair<long long, long long> CHT[N];
pair<long long, long long> point[N];

bool toLeft(int i, int j, int k){
	return 1.0 * (CHT[j].second - CHT[i].second) * (CHT[j].first - CHT[k].first) >= 1.0 * (CHT[k].second - CHT[j].second) * (CHT[i].first - CHT[j].first);
}

void addLine(long long m, long long b){
	CHT[sz] = make_pair(m, b);
	while(len >= 2 and toLeft(sz - 2, sz - 1, sz)){
		sz -= 1;
		CHT[sz] = make_pair(m, b);
	}
	sz++;
}

long long f(int pos, long long x){
	return CHT[pos].first * x + CHT[pos].second;
}

int main(){
	while(scanf("%d %d", &n, &M) == 2){
		long long prefix = 0;
		len = 0;
		at = sz = 0;
		addLine(0, 0);
		for(int i = 1; i <= n; i++){
			int x;
			scanf("%d", &x);
			prefix += x;
			while(at + 1 < sz and f(at, prefix) >= f(at + 1, prefix)) at += 1;
			memo[i] = f(at, prefix) + prefix * prefix + M;
			addLine(-2 * prefix, prefix * prefix + memo[i]);
		}
		printf("%lld\n", memo[n]);
	}
	return 0;
}
