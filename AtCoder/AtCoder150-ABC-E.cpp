#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that the optimal arrangement for the different positions is going from the

	  one with greatest c[i] to the smallest one.

	- So, we can sort c non increasingly and try to add the corresponding contribution, which ends up being:

	  coef(i) = 4^(n - i) * 2^(i - 1) * sum(binom(i - 1, k - 1) * k for all k = 1, ..., i)

	- According to the editorial, this can be further reduced, but in this idea we will

	  use FFT to compute the binomial coefficients denominators (since the numerator

	  is (i - 1)! for every term.

	  So we square the polynomial

	  P(x) = (0!)^{-1} + (1!)^{-1}x + (2!)^{-1}x^2 + ... + ((n - 1)!)^{-1}x^{n - 1}

	  And the final result's i-th element will contain:

	  (P(x)^2)[i] = sum(1 / (k! * (i - k)!) for all k = 0, ..., i)

	- After some manipulation, we get:

	  Q(i) = 2^(i - 1) + (i - 1)! * (P(x)^2)[i - 2]

	  so we have:

	  coef(i) = 4^(n - i) * 2^(i - 1) * Q(i)

	- Complexity: O(nlogn)

*/

const int N = 200000 + 5;
const int MOD = 1e9 + 7;

int add(int a, int b) {
	return (a + b) % MOD;
}

int mul(long long a, long long b) {
	return a * b % MOD;
}

int pow_mod(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

typedef vector<ll> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i,0,sz(res)) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

int n;
int c[N];
int Q[N];
int f[N];
int fi[N];
int pot4[N];

int solve() {
	int res = 0;
	int pot = 1;
	int sum_pot = 0;
	int prev_coef = 0;
	for(int i = 1; i <= n; i++) {
		pot <<= 1;
		if(pot >= MOD) pot -= MOD;
		res += mul(c[i], mul(mul(Q[i], pot), pot4[n - i]));
		if(res >= MOD) res -= MOD;
	}
	return res;
}

void init() {
	f[0] = 1;
	for(int i = 1; i < N; i++) f[i] = mul(i, f[i - 1]);
	fi[N - 1] = pow_mod(f[N - 1], MOD - 2);
	for(int i = N - 2; i >= 0; i--) fi[i] = mul(i + 1, fi[i + 1]);
	vl A(n), B(n);
	for(int i = 0; i < n; i++) A[i] = B[i] = fi[i];
	vl C = convMod<MOD>(A, B);
	int pot = 1;
	for(int i = 1; i <= n; i++) {
		Q[i] = pot;
		if(i >= 2) {
			Q[i] += mul(f[i - 1], C[i - 2]);
			if(Q[i] >= MOD) Q[i] -= MOD;
		}
		pot <<= 1;
		if(pot >= MOD) pot -= MOD;
	}
	pot4[0] = 1;
	for(int i = 1; i < N; i++) pot4[i] = mul(4, pot4[i - 1]);
}

int main() {
	scanf("%d", &n);
	init();
	for(int i = 1; i <= n; i++) scanf("%d", c + i);
	sort(c + 1, c + n + 1, greater<int>());
	printf("%d\n", solve());
	return 0;
}
