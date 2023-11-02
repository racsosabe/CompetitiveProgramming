#include<bits/stdc++.h>
using namespace::std;

long long a, m;

typedef unsigned long long ull;
typedef long double ld;
ull mod_mul(ull a, ull b, ull M) {
	return (__int128(a) * b) % M;
}
ull mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = mod_mul(ans, b, mod);
	return ans;
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for(auto a : A) {   // ^ count trailing zeroes
		ull p = mod_pow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = mod_mul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
ull pollard(ull n) {
	auto f = [n](ull x) { return mod_mul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = mod_mul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

long long phi(long long x){
	vector<unsigned long long> factors = factor(x);
	sort(factors.begin(), factors.end());
	factors.erase(unique(factors.begin(), factors.end()), factors.end());
	long long res = x;
	for(auto f : factors){
		x -= x / f;
	}
	return x;
}

vector<long long> D;

void backtracking(int pos, vector<pair<long long, int>> &v, long long prod){
	if(pos == v.size()){
		D.emplace_back(prod);
		return;
	}
	long long cur = 1;
	for(int i = 0; i <= v[pos].second; i++){
		backtracking(pos + 1, v, prod * cur);
		cur *= v[pos].first;
	}
}

void divisores(long long x){
	vector<ull> fact = factor(x);
	map<long long, int> F;
	for(auto f : fact) F[f] += 1;
	vector<pair<long long, int>> factors;
	for(auto e : F) factors.emplace_back(e);
	backtracking(0, factors, 1);
}

void no(){
	puts("Maradona e muito mais grande que o Pele");
}

int main(){
	scanf("%lld %lld", &a, &m);
	if(m == 1 or __gcd(a, m) != 1){
		no();
	}
	else{
		long long e = phi(m);
		divisores(e);
		long long ans = e;
		for(auto d : D){
			if(mod_pow(a, d, m) == 1) ans = min(ans, d);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
