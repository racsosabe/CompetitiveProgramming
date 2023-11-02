#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int M = 2000 + 5;

int s;
int t;
int m;
int n;
int a[N];
int b[N];
int c[M];
int d[M];

int check(int i, int j){
	if(t == 0) return false;
	int tA = c[i];
	int tB = d[j];
	int mini = min(tA, tB);
	tA -= mini;
	tB -= mini;
	int xA = tB;
	int xB = s - tA;
	if(xA >= s or xB <= 0) return false;
	int X = (xB + xA);
	int lo = 1, hi = t;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(X < b[mi] * 2) hi = mi;
		else lo = mi + 1;
	}
	if(a[lo] * 2 < X and X < b[lo] * 2) return true;
	return false;
}

bool solve(){
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			if(check(i, j)) return true;
		}
	}
	return false;
}

int main(){
	scanf("%d %d %d %d", &s, &t, &m, &n);
	for(int i = 1; i <= t; i++) scanf("%d", a + i);
	for(int i = 1; i <= t; i++) scanf("%d", b + i);
	for(int i = 1; i <= m; i++) scanf("%d", c + i);
	for(int i = 1; i <= n; i++) scanf("%d", d + i);
	puts(solve() ? "YES" : "NO");
	return 0;
}
