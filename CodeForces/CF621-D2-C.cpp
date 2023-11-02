#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int p;
int L[N];
int R[N];

int get(int l, int r){
	l = ((l + p - 1) / p) * p;
	r -= r % p;
	if(l > r) return 0;
	return (r - l) / p + 1;
}

long double solve(){
	long double ans = 0;
	for(int i = 0; i < n; i++){
		int j = i + 1 == n ? 0 : i + 1;
		long double pi = 1.0 * get(L[i], R[i]) / (R[i] - L[i] + 1);
		long double pj = 1.0 * get(L[j], R[j]) / (R[j] - L[j] + 1);
		ans += 2000.0 * (1 - (1 - pi) * (1 - pj));
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &p);
	for(int i = 0; i < n; i++) scanf("%d %d", L + i, R + i);
	printf("%.10Lf\n", solve());
	return 0;
}
