#include<bits/stdc++.h>
using namespace::std;

void setIO(string filename, bool input = true, bool output = true){
	string inputname = filename + ".in";
	string outputname = filename + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 1500 + 5;
const int M = 1500 * 1500 + 5;

int n;
int m;
int val[M];
int nxt[M];
int a[N][N];
int mapeo[M];
int memo[N][N];
int dx[] = {1, 0};
int dy[] = {0, 1};
vector<int> cells[N << 1];

void buildLevel(int lvl){
	sort(cells[lvl].begin(), cells[lvl].end(), [&] (int i, int j){
		if(val[i] == val[j]) return nxt[i] < nxt[j];
		return val[i] < val[j];
	});
	mapeo[cells[lvl][0]] = 0;
	for(int i = 1; i < cells[lvl].size(); i++){
		int at = cells[lvl][i];
		int pr = cells[lvl][i - 1];
		if(val[at]!= val[pr]){
			mapeo[at] = mapeo[pr] + 1;
		}
		else{
			mapeo[at] = mapeo[pr] + (nxt[at] != nxt[pr]);
		}
	}
}

int id(int i, int j){
	return i * m + j;
}

void solve(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int v = id(i, j);
			int dis = n - i + m - j - 2;
			val[i * m + j] = a[i][j];
			cells[dis].emplace_back(v);
		}
	}
	mapeo[id(n - 1, m - 1)] = 0;
	for(int i = 1; i <= n + m - 2; i++){
		for(auto e : cells[i]){
			int x = e / m;
			int y = e % m;
			int v = id(x, y);
			if(x + 1 >= n){
				memo[x][y] = 1;
				nxt[v] = mapeo[id(x, y + 1)];
			}
			else if(y + 1 >= m){
				memo[x][y] = 0;
				nxt[v] = mapeo[id(x + 1, y)];
			}
			else if(mapeo[id(x + 1, y)] < mapeo[id(x, y + 1)]){
				memo[x][y] = 0;
				nxt[v] = mapeo[id(x + 1, y)];
			}
			else{
				memo[x][y] = 1;
				nxt[v] = mapeo[id(x, y + 1)];
			}
		}
		buildLevel(i);
	}
	int x = 0;
	int y = 0;
	while(x + 1 != n or y + 1 != m){
		printf("%d ", a[x][y]);
		int dir = memo[x][y];
		x += dx[dir];
		y += dy[dir];
	}
	printf("%d\n", a[n - 1][m - 1]);
}

int main(){
	setIO("bemo");
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &a[i][j]);
		}
	}
	solve();
	return 0;
}
