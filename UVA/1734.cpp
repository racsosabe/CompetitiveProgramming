#include<bits/stdc++.h>
using namespace::std;

const int N = 12;
const int MASK = 1 << 10;
const int MOD = 1000000007;

int n;
int f[N];
int need;
int C[MASK];
int LSO[MASK];
vector<int> v;
int memo[MASK];
int last[MASK];
long long pot[N];
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

int DP(){
	for(int i = 0; i < MASK; i++){
		last[i] = (i > 0);
	}
	for(int pos = 1023; pos >= 1; pos--){
		memset(memo, 0, sizeof memo);
		for(int used = 0; used < MASK; used++){
			memo[used] = last[used];
			if((pos & used) == 0){
				memo[used] = add(memo[used], mul(C[pos], last[used | pos]));
			}
		}
		for(int used = 0; used < MASK; used++){
			last[used] = memo[used];
		}
	}
	return last[0];
}

void preprocess(){
	queue<tuple<int, int, int, int>> Q;
	Q.emplace(make_tuple(0, 0, 0, 0));
	memo2[0][0][0][0] = 1;
	vis2[0][0][0][0] = true;
	while(!Q.empty()){
		int pos, mask, menor, valid;
		tie(pos, mask, menor, valid) = Q.front();
		Q.pop();
		if(pos == v.size()) continue;
		int p = 1;
		int limit = menor ? 9 : v[pos];
		for(int d = 0; d <= limit; d++){
			int nmask, nmenor, nvalid;
			if(valid){
				nmask = mask | p;
				nmenor = menor | (d < v[pos]);
				nvalid = 1;
			}
			else{
				if(d == 0){
					nmask = mask;
					nmenor = menor | (d < v[pos]);
					nvalid = 0;
				}
				else{
					nmask = mask | p;
					nmenor = menor | (d < v[pos]);
					nvalid = 1;
				}
			}
			if(not vis2[pos + 1][nmask][nmenor][nvalid]){
				Q.emplace(make_tuple(pos + 1, nmask, nmenor, nvalid));
				vis2[pos + 1][nmask][nmenor][nvalid] = true;
			}
			memo2[pos + 1][nmask][nmenor][nvalid] = add(memo2[pos + 1][nmask][nmenor][nvalid], memo2[pos][mask][menor][valid]);
			p <<= 1;
		}
	}
	for(int mask = 0; mask < 1 << 10; mask++){
		C[mask] = add(memo2[v.size()][mask][0][1], memo2[v.size()][mask][1][1]);
	}
}

int solve(){
	v.clear();
	while(n > 0){
		v.emplace_back(n % 10);
		n /= 10;
	}
	reverse(v.begin(), v.end());
	memset(vis2, 0, sizeof vis2);
	memset(memo2, 0, sizeof memo2);
	preprocess();
	return DP();
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
