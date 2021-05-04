#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int N = 1000000 + 5;
const int E = 26;

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

int n;
string a;
string b;
int f[N];
int F[E];
int fi[N];

void init(){
	f[0] = 1;
	for(int i = 1; i < N; i++) f[i] = mul(i, f[i - 1]);
	fi[N - 1] = pow_mod(f[N - 1], MOD - 2);
	for(int i = N - 2; i >= 0; i--) fi[i] = mul(i + 1, fi[i + 1]);
}

int C(int n, int k){
	return mul(f[n], mul(fi[k], fi[n - k]));
}

int g(string &limit){
	for(int i = 0; i < E; i++) F[i] = 0;
	for(auto c : a) F[c - 'a'] += 1;
	int ans = 0;
	for(int i = 0; i < limit.size(); i++){
		int c = limit[i] - 'a';
		int extra = f[n - i - 1];
		for(auto x : F){
			extra = mul(extra, fi[x]);
		}
		for(int j = 0; j < c; j++){
			if(F[j] > 0){
				int cur_extra = mul(mul(extra, f[F[j]]), fi[F[j] - 1]);
				ans = add(ans, cur_extra);
			}
		}
		if(F[c] == 0) break;
		F[c] -= 1;
	}
	return ans;
}

int solve(){
	int ans = add(add(g(b), MOD - g(a)), MOD - 1);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> a >> b;
	n = a.size();
	init();
	printf("%d\n", solve());
	return 0;
}
