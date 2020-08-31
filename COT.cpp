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
const int LOG = 18;

int n;
int q;
int T;
vi G[N];
int len;
int w[N];
int a[N];
int h[N];
int in[N];
int val[N];
int out[N];
int nxt[N];
int par[N];
int subtree[N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++){
		S.insert(w[i]);
	}
	len = 0;
	map<int, int> id;
	for(set<int>::iterator it = S.begin(); it != S.end(); it++){
		int x = *it;
		val[len] = x;
		id[x] = len++;
	}
	for(int i = 1; i <= n; i++){
		w[i] = id[w[i]];
	}
}

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p) swap(G[u][i], G[u].back());
		int v = G[u][i];
		if(v == p) continue;
		DFS(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]) swap(G[u][i], G[u][0]);
	}
	if(p != -1){
		G[u].pop_back();
	}
}

void HLD(int u){
	in[u] = ++T;
	a[in[u]] = w[u];
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		h[v] = h[u] + 1;
		par[v] = u;
		nxt[v] = (v == G[u][0]? nxt[u] : v);
		HLD(v);
	}
	out[u] = T - 1;
}

int root[N];
int nodes = 0;
int L[2 * N + LOG * N];
int R[2 * N + LOG * N];
int st[2 * N + LOG * N];

void addNode(int x = 0){
	L[nodes] = R[nodes] = -1;
	st[nodes] = x;
	nodes += 1;
}

void build(int pos, int l = 0, int r = len - 1){
	if(l == r){
		st[pos] = 0;
		return;
	}
	int mi = (l + r) / 2;
	if(L[pos] == -1){
		L[pos] = nodes;
		addNode();
	}
	if(R[pos] == -1){
		R[pos] = nodes;
		addNode();
	}
	build(L[pos], l, mi);
	build(R[pos], mi + 1, r);
	st[pos] = st[L[pos]] + st[R[pos]];
}

void update(int x, int y, int last, int pos, int l = 0, int r = len - 1){
	if(l == r){
		st[pos] += y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi){
		R[pos] = R[last];
		L[pos] = nodes;
		addNode(st[L[last]]);
		update(x, y, L[last], L[pos], l, mi);
	}
	else{
		L[pos] = L[last];
		R[pos] = nodes;
		addNode(st[R[last]]);
		update(x, y, R[last], R[pos], mi + 1, r);
	}
	st[pos] = st[L[pos]] + st[R[pos]];
}

void init(){
	root[0] = nodes;
	addNode();
	build(root[0]);
	for(int i = 1; i <= n; i++){
		root[i] = nodes;
		addNode();
		update(a[i], 1, root[i - 1], root[i]);
	}
}

int query(int x, int y, int pos, int l = 0, int r = len - 1){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, L[pos], l, mi) + query(x, y, R[pos], mi + 1, r);
}

int getLeq(int a, int b, int x){
	int ans = 0;
	while(nxt[a] != nxt[b]){
		if(h[nxt[a]] < h[nxt[b]]) swap(a, b);
		ans += query(0, x, root[in[a]]) - query(0, x, root[in[nxt[a]] - 1]);
		a = par[nxt[a]];
	}
	if(h[a] > h[b]) swap(a, b);
	ans += query(0, x, root[in[b]]) - query(0, x, root[in[a] - 1]);
	return ans;
}

int solve(int a, int b, int k){
	int lo = 0, hi = len - 1;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(getLeq(a, b, mi) < k) lo = mi + 1;
		else hi = mi;
	}
	return val[lo];
}

int readInt(){
	char c = getchar();
	while(c == ' ' or c == '\n') c = getchar();
	int signo = 1;
	if(c == '-'){
		signo = -1;
		c = getchar();
	}
	int x = 0;
	while(c != ' ' and c != '\n'){
		x = (x<<1) + (x<<3) + c - '0';
		c = getchar();
	}
	return x * signo;
}

int main(){
	n = readInt();
	q = readInt();
	for(int i = 1; i <= n; i++) w[i] = readInt();
	for(int i = 1; i < n; i++){
		int u, v;
		u = readInt();
		v = readInt();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	compress();
	DFS(1);
	nxt[1] = 1;
	HLD(1);
	init();
	while(q--){
		int u, v, k;
		u = readInt();
		v = readInt();
		k = readInt();
		printf("%d\n", solve(u, v, k));
	}
	return 0;
}
