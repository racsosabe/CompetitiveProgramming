#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int MOD = 998244353;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int n;
int k;
int a[N];
int memo[N][N];
int prefix[N][N];

int f(int x){
	for(int i = 0; i <= n; i++) for(int j = 0; j <= k; j++) memo[i][j] = prefix[i][j] = 0;
	memo[1][1] = prefix[1][1] = 1;
	int pos = 0;
	int ans = 0;
	for(int i = 2; i <= n; i++){
		memo[i][1] = 1;
		for(int used = 2; used <= k; used++){
			while(pos + 1 < i and a[i] - a[pos + 1] >= x) pos += 1;
			memo[i][used] = prefix[pos][used - 1];
		}
		for(int used = 1; used <= k; used++){
			prefix[i][used] = add(prefix[i - 1][used], memo[i][used]);
		}
		ans = add(ans, memo[i][k]);
	}
	return ans;
}

int solve(){
	sort(a + 1, a + n + 1);
	int last = 0;
	int ans = 0;
	for(int i = a[n] / (k - 1); i >= 0; i--){
		int cur = f(i);
		ans = add(ans, mul(add(cur, MOD - last), i));
		last = cur;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%d\n", solve());
	return 0;
}
