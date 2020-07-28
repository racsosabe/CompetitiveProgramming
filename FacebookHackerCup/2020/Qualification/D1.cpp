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

	- Segment Tree problem.

	- This is just a particular case of D2, so please check that solution for more

	  references.

	- Complexity: O(n log(n + m)).
*/

const int N = 1000000+5;
const ll inf = 1e18;

int n;
int m;
int a;
int b;
int len;
int c[N];
int h[N];
int par[N];
ll st[8 * N];
bool inpath[N];
vector<int> G[N];
vector<int> path;
vector<ii> changes[N];

void build(){
	for(int i = 1; i <= 4 * len; i++){
		st[i] = inf;
	}
}

void update(int x, ll y, int pos = 1, int l = 1, int r = len){
	if(l == r){
		st[pos] = min(st[pos], y);
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2*pos, l, mi);
	else update(x, y, 2*pos+1, mi+1, r);
	st[pos] = min(st[2*pos], st[2*pos+1]);
}

ll query(int x, int y, int pos = 1, int l = 1, int r = len){
	if(y < l or r < x or x > y) return inf;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return min(query(x, y, 2*pos, l, mi), query(x, y, 2*pos+1, mi+1, r));
}

void getSubtree(int x){
	queue<int> Q;
	Q.emplace(x);
	vector<int> subtree;
	h[x] = 0;
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		if(c[u] > 0) subtree.emplace_back(u);
		for(int v : G[u]){
			if(inpath[v] or h[v] != -1) continue;
			h[v] = h[u] + 1;
			Q.emplace(v);
		}
	}
	if(subtree.empty()) return;
	sort(all(subtree), [&] (int i, int j){
		if(h[i] == h[j]) return c[i] < c[j];
		return h[i] < h[j];
	});
	for(int i = 0; i < subtree.size(); i++){
		if(i == 0 or h[subtree[i-1]] != h[subtree[i]]){
			changes[x].emplace_back(make_pair(h[subtree[i]], c[subtree[i]]));
		}
	}
}

void initPath(){
	queue<int> Q;
	Q.emplace(a);
	par[a] = -2;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			if(par[v] != -1) continue;
			par[v] = u;
			Q.emplace(v);
		}
	}
	path.clear();
	for(int x = b; x != -2; x = par[x]){
		path.emplace_back(x);
		inpath[x] = true;
	}
	reverse(all(path));
	for(int i = 1; i + 1 < path.size(); i++){
		getSubtree(path[i]);
	}
}

void download(int x, int steps){
	for(auto e : changes[x]){
		int need = steps + e.first;
		int to = steps + m - e.first;
		int cost = e.second;
		ll previous = query(need, len);
		if(previous == inf) continue;
		ll cur_cost = cost + previous;
		update(to, cur_cost);
	}
}

ll solve(){
	for(int i = 1; i <= n; i++){
		h[i] = -1;
		par[i] = -1;
		inpath[i] = false;
	}
	initPath();
	len = n + m;
	build();
	update(m, 0);
	for(int i = 1; i < path.size(); i++){
		download(path[i], i);
	}
	ll res = query(path.size() - 1, len);
	return res == inf? -1 : res;
}

void clearAll(){
	for(int i = 1; i <= n; i++){
		changes[i].clear();
		G[i].clear();
	}
}

void addEdge(int u, int v){
	G[u].emplace_back(v);
	G[v].emplace_back(u);
}

int main(){
	int t;
	ri(t);
	for(int caso = 1; caso <= t; caso++){
		ri2(n, m);
		a = 1;
		b = n;
		for(int i = 1; i <= n; i++){
			ri(c[i]);
			if(i - 1 >= 1) addEdge(i - 1, i);
			if(i + 1 <= n) addEdge(i + 1, i);
		}
		printf("Case #%d: %lld\n", caso, solve());
		if(caso < t) clearAll();
	}
	return 0;
}
