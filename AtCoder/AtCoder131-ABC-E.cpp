#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int k;
int M[N][N];

int main(){
	scanf("%d %d", &n, &k);
	if(k > (n - 1) * (n - 2) / 2){
		puts("-1");
		return 0;
	}
	for(int i = 2; i <= n; i++){
		M[1][i] = M[i][1] = 1;
	}
	int len = (n - 1) * (n - 2) / 2 - k;
	int x = 2, y = 3;
	for(int i = 0; i < len; i++){
		M[x][y] = M[y][x] = 1;
		y += 1;
		if(y == n + 1){
			x += 1;
			y = x + 1;
		}
	}
	vector< pair<int, int> > edges;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			if(M[i][j]) edges.emplace_back(make_pair(i, j));
		}
	}
	printf("%d\n", (int)edges.size());
	for(auto e : edges){
		printf("%d %d\n", e.first, e.second);
	}
	return 0;
}
