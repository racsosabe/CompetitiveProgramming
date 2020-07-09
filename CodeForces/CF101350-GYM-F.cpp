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

	- Easy "prefix sum" problem

	- Notice that we only care about the last joke the monkey heard: If that joke

	  has a frequency greater than 1, then the monkey will be on its seat, otherwise

	  there are two possible cases: The monkey hasn't heard any joke (it's on its seat)

	  or the joke has a frequency equal to 1 (the monkey is laughing).

	- We can propagate the queries by their id using a vector for each position

	  from 1 to n, so we add the query id to position L = max(1, x - k) and add

	  the query id in negative (that will mean that we must erase the query)

	  to position R + 1 = min(n, x + k) + 1.

	- We can iterate over all positions updating correspondingly and mantain an 

	  array of frequencies so we can answer each position in O(logn) if we use

	  a set to mantain the queries' ids.

	- Complexity: O(n + mlogm) per test.

*/

const int N = 100000+5;

int n;
int m;
vi Q[N];
int a[N];
int L[N];
int R[N];
int cnt[N];

void clearAll(){
	for(int i=1; i<=m; i++){
		cnt[a[i]] = 0;
	}
	for(int i=1; i<=n+1; i++) Q[i].clear();
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri2(n, m);
		for(int i=1; i<=m; i++){
			int x, l, k;
			ri3(x, a[i], k);
			L[i] = max(1, x - k);
			R[i] = min(n, x + k);
			Q[L[i]].emplace_back(i);
			Q[R[i]+1].emplace_back(-i);
		}
		int ans = 0;
		set<int> S;
		for(int i=1; i<=n; i++){
			for(auto x : Q[i]){
				if(x < 0){
					cnt[a[-x]] -= 1;
					S.erase(-x);
				}
				else{
					S.emplace(x);
					cnt[a[x]] += 1;
				}
			}
			if(S.empty()) ans += 1;
			else{
				if(cnt[a[*S.rbegin()]] > 1) ans += 1;
			}
		}
		printf("%d\n", ans);
		if(t) clearAll();
	}
	return 0;
}
