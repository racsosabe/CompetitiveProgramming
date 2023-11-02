#include<bits/stdc++.h>
using namespace::std;

const int LOG = 30;
const int N = 100000 + 5;

int n;
int m;
int L[N];
int R[N];
int a[N];
int b[N];
int ST[N][LOG];
int ac[LOG][N];

int query(int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1 << k;
	return ST[l][k] & ST[r - dis + 1][k];
}

void solve(){
	for(int i = 0; i < LOG; i++){
		for(int j = 1; j <= n; j++) ac[i][j] += ac[i][j - 1];
		int pot = 1 << i;
		for(int j = 1; j <= n; j++){
			if(ac[i][j]) b[j] |= pot;
		}
	}
	for(int i = 1; i <= n; i++){
		ST[i][0] = b[i];
	}
	for(int d = 1; 1 << d <= n; d++){
		int dis = 1 << (d - 1);
		for(int i = 1; i + 2 * dis - 1 <= n; i++){
			ST[i][d] = ST[i][d - 1] & ST[i + dis][d - 1];
		}
	}
	for(int i = 1; i <= m; i++){
		if(query(L[i], R[i]) != a[i]){
			puts("NO");
			return;
		}
	}
	puts("YES");
	for(int i = 1; i <= n; i++){
		printf("%d%c", b[i], " \n"[i == n]);
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d %d %d", L + i, R + i, a + i);
		for(int j = 0; j < LOG; j++){
			if(a[i] & (1 << j)){
				ac[j][L[i]] += 1;
				ac[j][R[i] + 1] -= 1;
			}
		}
	}
	solve();
	return 0;
}
