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

int n;
vi G[N];
int a[N];
int b[N];
int w[N];
int h[N];
ll ans[N];
int par[N];
viii edges;
bool vis[N];
int root[N];
int sizes[N];
int subtree[N];

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
}

void DFS(int u, int r){
	vis[u] = true;
	root[u] = r;
	subtree[u] = sizes[get(u)];
	for(int v : G[u]){
		if(vis[v]) continue;
		h[v] = h[u] + 1;
		DFS(v, r);
		subtree[u] += subtree[v];
	}
}

void solve(int L, int R, vi &p){
	vector<int> nodes;
	for(int i = L; i < R; i++){
		int u = get(a[p[i]]);
		int v = get(b[p[i]]);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		nodes.emplace_back(u);
		nodes.emplace_back(v);
	}
	for(auto x : nodes){
		if(vis[x]) continue;
		DFS(x, x);
	}
	for(int i = L; i < R; i++){
		int u = get(a[p[i]]);
		int v = get(b[p[i]]);
		int total = subtree[root[u]];
		if(h[u] > h[v]) swap(u, v);
		ans[p[i]] = 2LL * subtree[v] * (total - subtree[v]);
	}
	for(auto x : nodes){
		vis[x] = false;
		G[x].clear();
		h[x] = 0;
		root[x] = 0;
	}
}

int main(){
	ri(n);
	for(int i=1; i<n; i++){
		ri3(a[i], b[i], w[i]);
	}
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	vector<int> p(n - 1);
	iota(all(p), 1);
	sort(all(p), [&] (int i, int j){
		return w[i] < w[j];
	});
	int L = 0, R = 0;
	while(L < n - 1){
		while(R < n - 1 and w[p[L]] == w[p[R]]){
			R += 1;
		}
		solve(L, R, p);
		for(int i = L; i < R; i++){
			join(a[p[i]], b[p[i]]);
		}
		L = R;
	}
	ll best = *max_element(ans + 1, ans + n);
	vector<int> res;
	for(int i=1; i<n; i++){
		if(ans[i] == best) res.emplace_back(i);
	}
	printf("%lld %d\n", best, (int)res.size());
	for(int i=0; i<res.size(); i++){
		printf("%d%c", res[i], " \n"[i + 1 == res.size()]);
	}
	return 0;
}
