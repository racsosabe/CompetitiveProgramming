#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 10;
const int M = 100000 + 5;

int n;
int cnt[M];
int ac[N][N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		x1++; y1++;
		ac[x1][y1] += 1;
		ac[x1][y2 + 1] -= 1;
		ac[x2 + 1][y1] -= 1;
		ac[x2 + 1][y2 + 1] += 1;
	}
	int ans = 0;
	for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			ac[i][j] += ac[i][j - 1] + ac[i - 1][j] - ac[i - 1][j - 1];
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cnt[ac[i][j]] += 1;
		}
	}
	for(int i = 1; i <= n; i++){
		printf("%d\n", cnt[i]);
	}
	return 0;
}
