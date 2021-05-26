#include<bits/stdc++.h>
using namespace::std;

const int N = 15;
const int MASK = 1 << 10;
const int MOD = 1000000007;

int n;
int f[N];
int need;
int C[MASK];
int LSO[MASK];
vector<int> v;
long long pot[N];
bool vis[MASK][MASK];
int memo[MASK][MASK];
bool vis2[N][MASK][2][2];
int memo2[N][MASK][2][2];

inline int add(int a, int b){
	return (a + b) % MOD;
}	

inline int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

void init(){
	pot[0] = f[0] = 1;
	for(int i = 1; i < N; i++){
		f[i] = mul(f[i - 1], i);
		pot[i] = pot[i - 1] * 10;
	}
	for(int mask = 1; mask < 1 << 10; mask++){
		LSO[mask] = __builtin_ctz(mask);
	}
}

int DP2(int pos, int mask, int menor, int valid){
	if(pos == v.size()) return valid & (mask == need);
	if(vis2[pos][mask][menor][valid]) return memo2[pos][mask][menor][valid];
	int ans = 0;
	int limit = menor ? 9 : v[pos];
	int p = 1;
	for(int i = 0; i <= limit; i++){
		if(valid){
			if(need & p) ans = add(ans, DP2(pos + 1, mask | p, menor | (i < v[pos]), 1));
		}
		else{
			if(i == 0) ans = add(ans, DP2(pos + 1, mask, 1, 0));
			else if(need & (1 << i)) ans = add(ans, DP2(pos + 1, mask | p, menor | (i < v[pos]), 1));
		}
		p <<= 1;
	}
	vis2[pos][mask][menor][valid] = true;
	return memo2[pos][mask][menor][valid] = ans;
}

int DP(int pos, int used){
	if(pos == 1024) return used > 0;
	if(vis[pos][used]) return memo[pos][used];
	int ans = DP(pos + 1, used);
	if((pos & used) == 0) ans = add(ans, mul(C[pos], DP(pos + 1, used | pos)));
	vis[pos][used] = true;
	return memo[pos][used] = ans;
}

int solve(){
	v.clear();
	while(n > 0){
		v.emplace_back(n % 10);
		n /= 10;
	}
	reverse(v.begin(), v.end());
	for(int mask = 2; mask < 1 << 10; mask++){
		need = mask;
		memset(vis2, 0, sizeof vis2);
		C[mask] = DP2(0, 0, 0, 0);
	}
	memset(vis, 0, sizeof vis);
	return DP(1, 0);
}

int main(){
	int t;
	init();
	scanf("%d", &t);
	for(int caso = 1; caso <= t; caso++){
		scanf("%d", &n);
		printf("Case %d: %d\n", caso, solve());
	}
	return 0;
}
