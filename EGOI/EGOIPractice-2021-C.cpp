#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;
const int MOD = 1000000000 + 9;

int n;
int f[N];
long long d;
long long a[N];

int solve(){
	f[0] = 1;
	for(int i = 1; i <= n; i++) f[i] = (1ll * f[i - 1] * i) % MOD;
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++){
		if(a[i - 1] + d < a[i]) return 0;
	}
	int ans = 1;
	int L = 1, R = 1;
	while(L <= n){
		while(R <= n and a[L] == a[R]) R += 1;
		ans = (1ll * ans * f[R - L]) % MOD;
		L = R;
	}
	return ans;
}

int main(){
	scanf("%d %lld", &n, &d);
	for(int i = 1; i <= n; i++) scanf("%lld", a + i);
	printf("%d\n", solve());
	return 0;
}
