#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int m;
int h[N];
int a[N][N];

void build_level(int row){
	for(int i = 1; i <= m; i++){
		if(a[row - 1][i] == a[row][i]) h[i] += 1;
		else h[i] = 1;
	}
}

long long solve_row(int row){
	int l = 1, r = 1;
	vector<int> pos;
	long long res = 0;
	while(l <= m){
		while(r <= m and a[row][l] == a[row][r]) r++;
		for(int i = l; i < r; i++){
			while(!pos.empty() and h[pos.back()] >= h[i]){
				pos.pop_back();
			}
			res += 1ll * (h[i] - (pos.empty() ? 0 : h[pos.back()])) * (i - (pos.empty() ? l - 1 : pos.back()));
			pos.emplace_back(i);
		}
		pos.pop_back();
		while(!pos.empty()){
			int at = pos.back(); pos.pop_back();
			res += 1ll * (h[at] - (pos.empty() ? 0 : h[pos.back()])) * (r - 1 - (pos.empty() ? l - 1 : pos.back()));
		}
		l = r;
	}
	return res;
}

long long solve(){
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		build_level(i);
		ans += solve_row(i);
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &a[i][j]);
		}
	}
	printf("%lld\n", solve());
	return 0;
}
