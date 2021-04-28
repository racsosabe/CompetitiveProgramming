#include<bits/stdc++.h>
using namespace::std;

const int N = 400 + 5;
const int inf = 1e9;

int n;
int a[N];
int memo[N][N];

int main(){
	scanf("%d", &n);
	n <<= 1;
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) memo[i][j] = inf;
	}
	for(int i = 0; i + 1 < n; i++){
		memo[i][i + 1] = abs(a[i] - a[i + 1]);
	}
	for(int L = 4; L <= n; L += 2){
		for(int i = 0; i + L - 1 < n; i++){
			int j = i + L - 1;
			memo[i][j] = abs(a[i] - a[j]) + memo[i + 1][j - 1];
			for(int k = i; k < j; k++){
				memo[i][j] = min(memo[i][j], memo[i][k] + memo[k + 1][j]);
			}
		}
	}
	printf("%d\n", memo[0][n - 1]);
	return 0;
}
