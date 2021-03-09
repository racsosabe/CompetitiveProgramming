#include<bits/stdc++.h>
using namespace::std;

const int N = 300 + 5;

int n;
int a[N];
int memo[N][N];

int solve(){
	for(int l = 1; l <= n; l++){
		memo[l][l] = 1;
	}
	for(int len = 2; len <= n; len++){
		for(int l = 1; l + len - 1 <= n; l++){
			int r = l + len - 1;
			memo[l][r] = INT_MAX;
			for(int k = l; k < r; k++){
				memo[l][r] = min(memo[l][k] + memo[k + 1][r], memo[l][r]);
			}
			memo[l][r] -= (a[l] == a[r]);
		}
	}
	return memo[1][n];
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		a[i] -= 1;
	}
	printf("%d\n", solve());
	return 0;
}
