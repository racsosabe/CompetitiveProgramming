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

const int N = 20;
const int MASK = 1<<15;
const int inf = 1e9;

int n;
int m;
int len;
int p[N];
int deg[N];
int d[N][N];
bool vis[MASK];
int memo[MASK];

int DP(int mask){
	if(mask == 0) return 0;
	if(vis[mask]) return memo[mask];
	int ans = inf;
	int p1 = 31 - __builtin_clz(mask & (-mask));
	for(int m = mask & (mask - 1); m > 0; m &= m - 1){
		int p2 = 31 - __builtin_clz(m & (-m));
		int cand = d[p[p1]][p[p2]] + DP(mask ^ (1<<p1) ^ (1<<p2));
		ans = min(ans, cand);
	}
	vis[mask] = true;
	return memo[mask] = ans;
}

int main(){
	ri2(n, m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			d[i][j] = i == j? 0 : inf;
		}
	}
	int sum = 0;
	for(int i = 0; i < m; i++){
		int u, v, w;
		ri3(u, v, w);
		sum += w;
		deg[u] += 1;
		deg[v] += 1;
		d[u][v] = min(d[u][v], w);
		d[v][u] = d[u][v];
	}
	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	for(int i = 0; i < n; i++){
		if(deg[i] & 1){
			p[len++] = i;
		}
	}
	printf("%d\n", sum + DP((1<<len) - 1));
	return 0;
}
