#include<bits/stdc++.h>
using namespace::std;

/*
	Grand Prix of China - Problem F "Rooks"	

	Author: Racso Galvan

	Idea:

	- Just join all the rooks by row and by column (then sort them by the other axis) and check if two consecutive ones are from a different player.

	- Complexity: O((n + m)log(n + m))

*/

const int N = 400000 + 5;

int n;
int m;
int lenX;
int lenY;
int x[N];
int y[N];
bool vis[N];
vector<int> per_row[N];
vector<int> per_col[N];

void compress(){
	set<int> S;
	for(int i = 0; i < n + m; i++){
		S.emplace(x[i]);
	}
	map<int, int> id;
	for(auto x : S){
		id[x] = lenX++;
	}
	for(int i = 0; i < n + m; i++) x[i] = id[x[i]];
	S.clear();
	id.clear();
	for(int i = 0; i < n + m; i++){
		S.emplace(y[i]);
	}
	for(auto x : S){
		id[x] = lenY++;
	}
	for(int i = 0; i < n + m; i++) y[i] = id[y[i]];
}

int id(int pos){
	return pos < n;
}

void solve(){
	for(int i = 0; i < lenX; i++){
		sort(per_row[i].begin(), per_row[i].end(), [&] (int a, int b){
			return y[a] < y[b];
		});
		for(int j = 0; j < per_row[i].size(); j++){
			if(j > 0 and id(per_row[i][j]) ^ id(per_row[i][j - 1])) vis[per_row[i][j]] = true;
			if(j + 1 < per_row[i].size() and id(per_row[i][j]) ^ id(per_row[i][j + 1])) vis[per_row[i][j]] = true;
		}
	}
	for(int i = 0; i < lenY; i++){
		sort(per_col[i].begin(), per_col[i].end(), [&] (int a, int b){
			return x[a] < x[b];
		});
		for(int j = 0; j < per_col[i].size(); j++){
			if(j > 0 and id(per_col[i][j]) ^ id(per_col[i][j - 1])) vis[per_col[i][j]] = true;
			if(j + 1 < per_col[i].size() and id(per_col[i][j]) ^ id(per_col[i][j + 1])) vis[per_col[i][j]] = true;
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d %d", x + i, y + i);
	for(int i = 0; i < m; i++) scanf("%d %d", x + i + n, y + i + n);
	compress();
	for(int i = 0; i < n + m; i++){
		per_row[x[i]].emplace_back(i);
		per_col[y[i]].emplace_back(i);
	}
	solve();
	for(int i = 0; i < n; i++){
		putchar('0' + vis[i]);
	}
	putchar('\n');
	for(int i = 0; i < m; i++){
		putchar('0' + vis[i + n]);
	}
	putchar('\n');
	return 0;
}
