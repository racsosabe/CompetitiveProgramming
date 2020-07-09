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

const int N = 200000+5;
const int E = 400000+5;
const int LOG = 21;

int n;
int m;
int edges;
ll ans[N];
int to[E];
int sum[N];
int nxt[E];
int par[N];
int last[N];
int pedge[N];
int level[N];
int ST[N][LOG];

void computeLCA(int u, int p){
	ST[u][0] = p;
	for(int d = 1; 1<<d <= level[u]; d++){
		ST[u][d] = ST[p][0];
		p = ST[p][d];
	}
}

void addEdge(int u, int v){
	to[edges] = v;
	nxt[edges] = last[u];
	last[u] = edges;
	edges += 1;
}

void DFS(int u){
	computeLCA(u, par[u]);
	for(int e = last[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(v == par[u]) continue;
		level[v] = level[u] + 1;
		pedge[v] = e;
		par[v] = u;
		DFS(v);
	}
}

void goUp(int &a, int dis){
	for(int i = 0; i < LOG; i++){
		if(dis & (1<<i)) a = ST[a][i];
	}
}

int lca(int u, int v){
	if(level[u] < level[v]) swap(u, v);
	goUp(u, level[u] - level[v]);
	if(u == v) return u;
	for(int i = LOG - 1; i >= 0; i--){
		if(ST[u][i] != ST[v][i]){
			u = ST[u][i];
			v = ST[v][i];
		}
	}
	return ST[u][0];
}

ll f(int initial, int limit){
	return initial * limit + limit * (limit - 1) / 2;
}

void update(int u, int v, int w){
	int l = lca(u, v);
	int val = 1;
	while(u != l and w){
		int take = min(w, val);
		sum[pedge[u]] += take;
		w -= take;
		val += 1;
		u = par[u];
	}
	if(!w) return;
	int lo = 0, hi = min((int)(sqrt(2 * w)), level[v] - level[l]);
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(f(val, mi) <= w) lo = mi;
		else hi = mi - 1;
	}
	if(w > f(val, lo) and lo < level[v] - level[l]){
		int adding = w - f(val, lo);
		int carry = v;
		goUp(carry, level[v] - level[l] - lo - 1);
		sum[pedge[carry]] += adding;
		w -= adding;
	}
	goUp(v, level[v] - level[l] - lo);
	val += lo - 1;
	while(v != l){
		sum[pedge[v]] += val;
		w -= val;
		val -= 1;
		v = par[v];
	}
}

void DFS2(int u){
	for(int e = last[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(v == par[u]) continue;
		ans[v] += sum[e] + ans[u];
		DFS2(v);
	}
}

int main(){
	ri(n);
	for(int i=1; i<=n; i++) last[i] = -1;
	for(int i=1; i<n; i++){
		int u, v;
		ri2(u, v);
		addEdge(u, v);
		addEdge(v, u);
	}
	DFS(1);
	ri(m);
	for(int i=1; i<=m; i++){
		int u, v, w;
		ri3(u, v, w);
		update(u, v, w);
	}
	DFS2(1);
	printf("%lld\n", *max_element(ans + 1, ans + 1 + n));
	return 0;
}
