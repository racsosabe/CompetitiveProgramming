#include<bits/stdc++.h>
using namespace::std;

const int N = 2025;

int n;
int r;
int m;
int f[N];
int pf[N];
int pot[N];
int C[N][N];
int ways[N];
int memo[N][N];

int add(long long a, long long b, int m){
	return (a + b) % m;
}

int mul(long long a, long long b, int m){
	return (1ll * a * b) % m;
}

void init(){
	int m2 = m & 1 ? m : 2 * m;
	C[0][0] = 1 % m2;
	for(int i = 1; i < N; i++){
		C[i][i] = C[i][0] = 1 % m2;
		for(int j = 1; j < i; j++){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % m2;
		}
	}
	ways[0] = 1;
	ways[1] = 1;
	for(int i = 2; i <= n; i++){
		for(int j = 0; j <= i - 1; j++){
			ways[i] = add(ways[i], mul(C[i - 1][j], mul(ways[j], ways[i - 1 - j], m2), m2), m2);
		}
		if(m2 == 2 * m) ways[i] /= 2;
		else ways[i] = mul(ways[i], (m + 1) / 2, m);
	}
	C[0][0] = 1 % m;
	for(int i = 1; i < N; i++){
		C[i][i] = C[i][0] = 1 % m;
		for(int j = 1; j < i; j++){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % m;
		}
	}
}

int solve(){
	r = n + 1 - r;
	for(int i = r; i <= n; i++){
		memo[i][r] = ways[i];
		for(int k = 1; k <= i - r; k++){
			memo[i][r] = add(memo[i][r], m - mul(C[i - r][k], mul(memo[i - k][r], ways[k + 1], m), m), m);
		}
	}
	return memo[n][r];
}

int main(){
	scanf("%d %d %d", &r, &n, &m);
	init();
	printf("%d\n", solve());
	return 0;
}
