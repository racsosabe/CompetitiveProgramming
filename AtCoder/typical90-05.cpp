#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

typedef vector<ll> vl;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, M_PIl / k); // M_PI, lower-case L
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

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

const int B = 1000 + 5;

int b;
int k;
int len;
int R[N];
long long n;
int memo[B][B];
long long cnt[B];
vector<int> valid;

int solve(){
	memo[len][0] = 1;
	for(int i = len - 1; i >= 0; i--){
		for(int r = 0; r < b; r++){
			for(auto x : valid){
				int nr = (cnt[i] * R[i] * x + r) % b;
				memo[i][r] += memo[i + 1][nr];
				if(memo[i][r] >= MOD) memo[i][r] -= MOD;
			}
		}
	}
	return memo[0][0];
}

int getCycleLength(){
	vector<bool> vis(b, false);
	int ans = 0;
	int p = 1 % b;
	while(!vis[p]){
		R[ans] = p;
		vis[p] = true;
		p = (10 * p) % b;
		ans += 1;
	}
	return ans;
}

int main(){
	scanf("%lld %d %d", &n, &b, &k);
	for(int i = 1; i <= k; i++){
		int x;
		scanf("%d", &x);
		valid.emplace_back(x);
	}
	len = getCycleLength();
	for(int i = 0; i < len; i++){
		if(n >= i + 1){
			cnt[i] = ((n - i - 1) / len + 1) % b;
		}
	}
	for(int i = 0; i < len; i++){
		cout << i << " -> " << cnt[i] << endl;
	}
	printf("%d\n", solve());
	return 0;
}
