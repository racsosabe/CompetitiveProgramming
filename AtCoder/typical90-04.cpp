#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int n;
int m;
int row[N];
int col[N];
int a[N][N];

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &a[i][j]);
			row[i] += a[i][j];
			col[j] += a[i][j];
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("%d%c", row[i] + col[j] - a[i][j], " \n"[j + 1 == m]);
		}
	}
	return 0;
}
