#include<bits/stdc++.h>
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ri(x) scanf("%d",&(x))
#define ri2(x,y) scanf("%d %d",&(x),&(y))
#define ri3(x,y,z) scanf("%d %d %d",&(x),&(y),&(z))
#define rll(x) scanf("%lld",&(x))
#define rll2(x,y) scanf("%lld %lld",&(x),&(y))
#define rll3(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z))
#define gc(x) ((x) = getchar())
using namespace::std;

const long double PI = acos(-1);
const long long MOD = 1000000000 +7;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> tll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<tll> vtll;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ii> sii;
typedef set<iii> siii;

ll gcd(ll a, ll b){ return b==0?a:gcd(b,a%b);}

ll add(ll a, ll b, ll m = MOD){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	if(a < 0) a += m;
	if(b < 0) b += m;
	ll res = a+b;
	if(res >= m or res <= -m) res %= m;
	if(res < 0) res += m;
	return res;
}

ll mul(ll a, ll b, ll m = MOD){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	if(a < 0) a += m;
	if(b < 0) b += m;
	ll res = a*b;
	if(res >= m or res <= -m) res %= m;
	if(res < 0) res += m;
	return res;
}

ll pow_mod(ll a, ll b, ll m = MOD){
	ll res = 1LL;
	a = a%m;
	while(b){
		if(b&1) res = mul(res,a,m);
		b >>= 1;
		a = mul(a,a,m);
	}
	return res;
}

ll fastexp(ll a, ll b){
	ll res = 1LL;
	while(b){
		if(b&1) res = res*a;
		b >>= 1;
		a *= a;
	}
	return res;
}

int gcdExtendido(int a, int b, int *x, int *y){
	if(a == 0){
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtendido(b%a,a,&x1,&y1);
	
	*x = y1-(b/a)*x1;
	*y = x1;
	return gcd;
}

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/

/*
	Author: Racso Galvan

	Idea:

	- Very interesting (but classic (?)) Suffix Array problem.

	- Just notice that if we fix the length of the repeated string as L, we can

	  iterate over all multiple indices of the string (i * L, (i + 1) * L).

	  Then, we will get the LCP of i * L and (i + 1) * L and if the value is cur

	  we will have some repetitions only if cur >= L (since if cur < L the string
	  
	  repeated wouldn't have length of at least L). The number of repetitions

	  is floor(cur / L) + 1, the first term because of the LCP and the second one

	  because we have a repetition between positions i * L and (i + 1) * L.

	  Now, the only way to improve that answer considering that LCP is to append

	  some letters at the start of the substring to make it a greater repeated

	  string.

	- Then, the best way to improve the solution is to add exactly the number of 
	 
	  letters needed to add 1 to the current answer (since adding 2 would be considered
	  
	  in the previous iteration or it's impossible to do so).

	  Now, since the LCP is fixed


*/

// Lexicographically minimum suffix array & LCP array construction
// SA: O(nlogn), LCP: O(n)

vector<int> suffix_array(vector<int> &s, int char_bound = -1) {
	int n = s.size();
	vector<int> a(n);
	if (n == 0) {
		return a;
	}
	if (char_bound != -1) {
		vector<int> aux(char_bound, 0);
		for (int i = 0; i < n; i++) {
			aux[s[i]]++;
		}
		int sum = 0;
		for (int i = 0; i < char_bound; i++) {
			int add = aux[i];
			aux[i] = sum;
			sum += add;
		}
		for (int i = 0; i < n; i++) {
			a[aux[s[i]]++] = i;
		}
	} else {
		iota(a.begin(), a.end(), 0);
		sort(a.begin(), a.end(), [&](int i, int j) { return s[i] < s[j]; });
	}
	vector<int> sorted_by_second(n);
	vector<int> ptr_group(n);
	vector<int> new_group(n);
	vector<int> group(n);
	group[a[0]] = 0;
	for (int i = 1; i < n; i++) {
		group[a[i]] = group[a[i - 1]] + (!(s[a[i]] == s[a[i - 1]]));
	}
	int step = 1;
	while (step < n) {
		int at = 0;
		for(int i = 0; i < n; i++){
			sorted_by_second[at++] = a[i] - step < 0? a[i] - step + n : a[i] - step;
		}
		for (int i = n - 1; i >= 0; i--) {
			ptr_group[group[a[i]]] = i;
		}
		for (int i = 0; i < n; i++) {
			int x = sorted_by_second[i];
			a[ptr_group[group[x]]++] = x;
		}
		new_group[a[0]] = 0;
		for (int i = 1; i < n; i++) {
			if (group[a[i]] != group[a[i - 1]]) {
				new_group[a[i]] = new_group[a[i - 1]] + 1;
			} else {
				int pre = (a[i - 1] + step >= n ? group[a[i - 1] + step - n] : group[a[i - 1] + step]);
				int cur = (a[i] + step >= n ? group[a[i] + step - n] : group[a[i] + step]);
				new_group[a[i]] = new_group[a[i - 1]] + (pre != cur);
			}
		}
		swap(group, new_group);
		step <<= 1;
	}
	sort(a.begin(),a.end(),[&](int i, int j){
		if(group[i] == group[j]) return i < j;
		return group[i] < group[j];
	});
	return a;
}

vector<int> lcp_construction(vector<int> &s, vector<int> &a){
	int n = s.size();
	vector<int> rank(n, 0);
	for(int i=0; i<n; i++){
		rank[a[i]] = i;
	}
	int k = 0;
	vector<int> lcp(n-1,0);
	for(int i=0; i<n; i++){
		if(rank[i] == n-1){
			k = 0;
			continue;
		}
		int j = a[rank[i]+1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k += 1;
		lcp[rank[i]] = k;
		if(k > 0) k -= 1;
	}
	return lcp;
}

const int N = 50000+5;

int n;
char s[N];
vector<vi> ST;
vector<int> pos;

void build(vector<int> &v){
	int len = v.size();
	ST.resize(len);
	for(int i=0; i<len; i++){
		ST[i].clear();
		ST[i].emplace_back(v[i]);
	}
	for(int d=1; 1<<d <= len; d++){
		int dis = 1<<(d-1);
		for(int i=0; i+2*dis-1 < len; i++){
			ST[i].emplace_back(min(ST[i][d-1], ST[i+dis][d-1]));
		}
	}
}

int query(int l, int r){
	l = pos[l];
	r = pos[r];
	if(l > r) swap(l, r);
	r -= 1;
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1<<k;
	return min(ST[l][k], ST[r-dis+1][k]);
}

int solve(){
	int ans = 1;
	for(int L = 1; L <= n; L++){
		for(int i = 0; i + L < n; i += L){
			int cur = query(i, i + L);
			if(cur >= L) ans = max(ans, cur / L + 1);
			if(i >= L - cur % L){
				int cur2 = query(i - L + cur % L, i + cur % L);
				if(cur2 >= L) ans = max(ans, cur2 / L + 1);
			}
		}
	}
	return ans;
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri(n);
		vector<int> v(n + 1, 0);
		for(int i=0; i<n; i++){
			char c = getchar();
			while(!isalpha(c)) c = getchar();
			v[i] = c;
		}
		vector<int> sa = suffix_array(v);
		vector<int> lcp = lcp_construction(v, sa);
		build(lcp);
		pos.resize(n + 1);
		for(int i=0; i<sa.size(); i++){
			pos[sa[i]] = i;
		}
		printf("%d\n", solve());
	}
	return 0;
}
