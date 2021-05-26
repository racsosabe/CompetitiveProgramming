#include<bits/stdc++.h>
using namespace::std;

const int M = 6;
const int LOG = 19;
const int N = 100000 + 5;

int n;
int m;
int k;
int a[M][N];
int ST[M][N][LOG];

void build(int id){
	for(int i = 1; i <= n; i++){
		ST[id][i][0] = a[id][i];
	}
	for(int d = 1; 1 << d <= n; d++){
		int dis = 1 << (d - 1);
		for(int i = 1; i + 2 * dis - 1 <= n; i++){
			ST[id][i][d] = max(ST[id][i][d - 1], ST[id][i + dis][d - 1]);
		}
	}
}

int query(int id, int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1 << k;
	return max(ST[id][l][k], ST[id][r - dis + 1][k]);
}

int C(int l, int r){
	int ans = 0;
	for(int i = 0; i < m; i++){
		ans += query(i, l, r);
	}
	return ans;
}

void solve(){
	int r = 1;
	int L = -1, R = -1;
	for(int l = 1; l <= n; l++){
		r = max(r, l);
		while(r <= n and C(l, r) <= k){
			r += 1;
		}
		int len = r - l;
		if(len == 0) continue;
		if(L == -1 or R - L + 1 < len){
			L = l;
			R = r - 1;
		}
	}
	vector<int> ans(m, 0);
	for(int j = 0; j < m; j++) ans[j] = query(j, L, R);
	for(int i = 0; i < m; i++){
		printf("%d%c", ans[i], " \n"[i + 1 == m]);
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &a[j][i]);
		}
	}
	for(int i = 0; i < m; i++) build(i);
	solve();
	return 0;
}
