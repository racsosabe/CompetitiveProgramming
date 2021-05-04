#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int c[N];
int p[N][5];
int par[N << 1];
int sizes[N << 1];

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
}

int solve(){
	for(int i = 1; i <= m; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 4; j += 2){
			join(p[i][j], p[i][j + 1]);
		}
	}
	vector<int> perm(n);
	iota(perm.begin(), perm.end(), 1);
	sort(perm.begin(), perm.end(), [&] (int i, int j){
		return c[i] < c[j];
	});
	int ans = 0;
	for(int i : perm){
		if(get(p[i][0]) == get(p[i][2])) continue;
		join(p[i][0], p[i][2]);
		ans += c[i];
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	m = n << 1;
	for(int i = 1; i <= n; i++){
		scanf("%d", &c[i]);
		for(int j = 0; j < 4; j++) scanf("%d", &p[i][j]);
	}
	printf("%d\n", solve());
	return 0;
}
