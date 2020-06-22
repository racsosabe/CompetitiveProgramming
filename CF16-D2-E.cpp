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

	- Let's use an array memo[mask] that gives us the probability that the fish

	  from the set mask are alive in some day, then we must consider every fish

	  that is not in mask as the last eaten fish.

	  Notice that the order for mask processing must be by decreasing number of

	  bits on.

	- Thus, we can fix the last eaten fish as p (with mask & (1<<p) = 0) and

	  we have to add up the probability that each of the fish in mask eats it,

	  which will be:

	  P(mask, p) = sum for x in mask of a[x][p] * prob(size(mask) + 1)

	  Where prob(len) is the probability for a pair (i, j), 1 <= i <= j <= len

	  to be chosen given that all the pairs are equiprobable.

	  It's easy to notice that prob(len) = 2 / (len * (len + 1))

	- We can preprocess the probabilities P(mask, p) by first computing the sums
       
	  for each mask that doesn't contain p and then multiplying them by the probability 

	  of getting a certain pair.

	- Complexity: O(n * 2^n)
*/

const int N = 20;
const int MASK = (1<<18) + 5;

int n;
double p[N][N];
double memo[MASK];
double sum[N][MASK];

void solve(){
	for(int i=0; i<n; i++){
		sum[i][0] = 0.0;
		for(int mask=1; mask<1<<n; mask++){
			if(mask & (1<<i)) continue;
			int l = 31 - __builtin_clz(mask & (-mask));
			sum[i][mask] = p[l][i] + sum[i][mask & (mask - 1)];
		}
		for(int mask=1; mask<1<<n; mask++){
			if(mask & (1<<i)) continue;
			int len = __builtin_popcount(mask);
			sum[i][mask] *= 2.0 / (len * (len + 1));
		}
	}
	vector<int> masks((1<<n) - 2);
	iota(all(masks),1);
	sort(all(masks), [&](int i, int j){
		return __builtin_popcount(i) > __builtin_popcount(j);
	});
	memo[(1<<n)-1] = 1.0;
	for(auto x : masks){
		int len = __builtin_popcount(x);
		for(int i=0; i<n; i++){
			if(x & (1<<i)) continue;
			memo[x] += (memo[x | (1<<i)] * sum[i][x]);
		}
	}
}

int main(){
	ri(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%lf",&p[i][j]);
		}
	}
	solve();
	for(int i=0; i<n; i++){
		printf("%.7lf%c",memo[1<<i]," \n"[i + 1 == n]);
	}
	return 0;
}
