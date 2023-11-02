#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

void setIO(string filename, bool input = true, bool output = true){
	string inputname = filename + ".in";
	string outputname = filename + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

int n;
int h[N];
int len[2];
int ans[N];
int v[N][N];
int mini[2][N];
int value[2][N];

void init(){
	len[0] = len[1] = 0;
	for(int i = 0; i < 2; i++) mini[i][0] = value[i][0] = INT_MAX;
}

void pop(){
	if(len[1] == 0){
		while(len[0] > 0){
			int x = value[0][len[0]];
			value[1][len[1] + 1] = x;
			mini[1][len[1] + 1] = min(x, mini[1][len[1]]);
			len[1] += 1;
			len[0] -= 1;
		}
	}
	len[1] -= 1;
}

void solveRow(int r){
	for(int i = n; i >= 1; i--){
		if(v[r][i]) h[i] += 1;
		else h[i] = 0;
	}
	init();
	int cur = 0;
	for(int i = n; i >= 1; i--){
		cur += 1;
		value[0][len[0] + 1] = h[i];
		mini[0][len[0] + 1] = min(mini[0][len[0]], h[i]);
		len[0] += 1;
		while(len[0] + len[1] > cur) pop();
		while(cur > 0 and min(mini[0][len[0]], mini[1][len[1]]) < cur){
			cur -= 1;
			pop();
		}
		ans[cur] += 1;
	}
}

void solve(){
	for(int i = 1; i <= n; i++){
		solveRow(i);
	}
	for(int i = n - 1; i >= 1; i--) ans[i] += ans[i + 1];
}

int main(){
	setIO("custi");
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &v[i][j]);
		}
	}
	solve();
	for(int i = 1; i <= n; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
