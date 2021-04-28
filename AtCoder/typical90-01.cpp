#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int k;
int L;
int a[N];
int d[N];

bool can(int x){
	int cnt = 0;
	int cur = 0;
	for(int i = 1; i <= n + 1; i++){
		cur += d[i];
		if(cur >= x){
			cnt += 1;
			cur = 0;
		}
	}
	if(cur >= x) cnt += 1;
	return cnt >= k + 1;
}

int main(){
	scanf("%d %d", &n, &L);
	scanf("%d", &k);
	a[n + 1] = L;
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	for(int i = 1; i <= n + 1; i++){
		d[i] = a[i] - a[i - 1];
	}
	int lo = 1, hi = L;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(can(mi)) lo = mi;
		else hi = mi - 1;
	}
	printf("%d\n", lo);
	return 0;
}
