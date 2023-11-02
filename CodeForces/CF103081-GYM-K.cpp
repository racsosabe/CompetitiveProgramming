#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int N = 300000 + 5;
const int B = 311;

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
string s;
int pot[N];
int poti[N];
int prefix[N];

void init(){
	pot[0] = 1;
	for(int i = 1; i < N; i++) pot[i] = mul(B, pot[i - 1]);
	poti[N - 1] = pow_mod(pot[N - 1], MOD - 2);
	for(int i = N - 2; i >= 0; i--) poti[i] = mul(B, poti[i + 1]);
}

int get(int l, int r){
	return mul(poti[l], add(prefix[r], MOD - prefix[l - 1]));
}

bool can(int len){
	map<int, int> F;
	for(int i = len; i <= n; i++){
		F[get(i - len + 1, i)] += 1;
	}
	for(auto e : F) if(e.second == 1) return true;
	return false;
}

string get(int len){
	map<int, int> F;
	for(int i = len; i <= n; i++){
		F[get(i - len + 1, i)] += 1;
	}
	for(int i = len; i <= n; i++){
		if(F[get(i - len + 1, i)] == 1){
			return s.substr(i - len, len);
		}
	}
}

string solve(){
	for(int i = 1; i <= n; i++){
		prefix[i] = add(mul(s[i - 1] - 'A' + 1, pot[i]), prefix[i - 1]);
	}
	int lo = 1, hi = n;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(!can(mi)) lo = mi + 1;
		else hi = mi;
	}
	return get(lo);
}

int main(){
	init();
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	n = s.size();
	cout << solve() << endl;
	return 0;
}
