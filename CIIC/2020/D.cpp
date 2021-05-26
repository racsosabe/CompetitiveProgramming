#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1e9;
const int K = 50 + 5;
const int LOG = 31;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int n;
int k;
int C[K][K];
int f[LOG][K];

void preprocess(){
	for(int i = 0; i < K; i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++){
			C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
		}
	}
	for(int i = 0; i <= k; i++) f[0][i] = 1;
	int pot = 1;
	for(int b = 1; b < LOG; b++){
		for(int j = 0; j <= k; j++){
			int cur = 1;
			f[b][j] = f[b - 1][j];
			for(int p = 0; p <= j; p++){
				f[b][j] = add(f[b][j], mul(mul(C[j][p], f[b - 1][j - p]), cur));
				cur = mul(cur, pot);
			}
		}
		pot = add(pot, pot);
	}
}

int g(int x){
	int ans = 0;
	int sum = 0;
	int pot = 1;
	for(int i = 0; i < LOG; i++){
		if(x & 1){
			int cur = 1;
			for(int j = 0; j <= k; j++){
				ans = add(ans, mul(mul(C[k][j], f[i][k - j]), cur));
				cur = mul(cur, sum);
			}
			sum += pot;
		}
		pot <<= 1;
		x >>= 1;
	}
	return ans;
}

int solve(){
	int l = 1;
	int ans = 0;
	while(l <= n){
		int val = n / l;
		int r = n / val;
		ans = add(ans, mul(val, add(g(r), MOD - g(l - 1))));
		l = r + 1;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	preprocess();
	printf("%d\n", solve());
	return 0;
}
