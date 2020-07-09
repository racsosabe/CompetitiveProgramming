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

const int N = 100000+5;
const int LOG = 18;

int n;
int q;
int a[N];
int STMax[N][LOG];
int STMin[N][LOG];

int queryMax(int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1<<k;
	return max(STMax[l][k], STMax[r - dis + 1][k]);
}

int queryMin(int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1<<k;
	return min(STMin[l][k], STMin[r - dis + 1][k]);
}

int main(){
	ri(n);
	for(int i=0; i<n; i++){
		ri(a[i]);
		STMax[i][0] = STMin[i][0] = a[i];
	}
	for(int d = 1; 1<<d <= n; d++){
		int dis = 1<<(d-1);
		for(int i=0; i + 2*dis - 1 < n; i++){
			STMin[i][d] = min(STMin[i][d-1], STMin[i+dis][d-1]);
			STMax[i][d] = max(STMax[i][d-1], STMax[i+dis][d-1]);
		}
	}
	ri(q);
	int l, r;
	while(q--){
		ri2(l, r);
		int min_in_range = queryMin(l, r);
		int max_in_range = queryMax(l, r);
		int max_out_range = max((l > 0? queryMax(0, l - 1) : 0), (r + 1 < n? queryMax(r + 1, n - 1) : 0));
		int ans = max(2 * (min_in_range + max_out_range), min_in_range + max_in_range);
		printf("%d.%d\n", ans >> 1, (ans & 1? 5 : 0));
	}
	return 0;
}
