#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int MOD = 1000000000 + 7;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int n;
int a[N];
char s[N];
bool vis[N][N][2];
int memo[N][N][2];

bool balanced(){
	int prefix = 0;
	for(int i = 0; i < n; i++){
		if(s[i] == '(') prefix += 1;
		else if(prefix == 0) return false;
		else prefix -= 1;
	}
	return prefix == 0;
}

int DP(int pos, int balance, bool menor){
	if(pos == n) return balance == 0;
	if(vis[pos][balance][menor]) return memo[pos][balance][menor];
	int ans = 0;
	int limit = menor ? 1 : a[pos];
	for(int i = 0; i <= limit; i++){
		int nbalance = balance + 2 * (1 - i) - 1;
		bool nmenor = menor | (i < a[pos]);
		if(nbalance >= 0) ans = add(ans, DP(pos + 1, nbalance, nmenor));
	}
	vis[pos][balance][menor] = true;
	return memo[pos][balance][menor] = ans;

}

int solve(){
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < n; i++){
		a[i] = s[i] == ')';
	}
	return DP(0, 0, 0);
}

int main(){
	scanf("%d", &n);
	int ans = 0;
	for(int i = 0; i < 2; i++){
		scanf("%s", s);
		int act = solve();
		ans = add(ans, mul(MOD + 2 * i - 1, act));
		if(i == 0 and balanced()) ans = add(ans, 1);
	}
	printf("%d\n", ans);
	return 0;
}
