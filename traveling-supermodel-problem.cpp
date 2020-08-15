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

const int N = 15;
const int M = 1<<15;
const int inf = 1e9;

int n;
int m;
int target;
int a[N][N];
int memo[N][N][M];
bool vis[N][N][M];

int DP(int a1, int a2, int mask){
	if(!mask) return 0LL;
	if(!(mask & target)) return -inf;
	if(vis[a1][a2][mask]) return memo[a1][a2][mask];
	int ans = -inf;
	for(int m = mask; m > 0; m &= m - 1){
		int nxt = 31 - __builtin_clz(m & (-m));
		if(a[a2][nxt] == -1) continue;
		int cand = a[a1][a2] * a[a2][nxt] + DP(a2, nxt, mask ^ (1 << nxt));
		if(ans < cand) ans = cand;
	}
	vis[a1][a2][mask] = true;
	return memo[a1][a2][mask] = ans;
}

int main(){
	ri2(n, m);
	memset(a, -1, sizeof a);
	for(int i = 0; i < m; i++){
		int u, v, c;
		ri3(u, v, c);
		u--; v--;
		a[u][v] = a[v][u] = c;
	}
	target = 1 << (n - 1);
	int ans = 0;
	int total = (1 << n) - 1;
	for(int j = 1; j < n; j++){
		if(a[0][j] == -1) continue;
		ans = max(ans, DP(0, j, total ^ 1 ^ (1 << j)));
	}
	printf("%d\n", ans);
	return 0;
}
