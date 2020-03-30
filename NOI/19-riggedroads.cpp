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

	- Consider the MST formed by the set of edges given, then the non-MST edges

	  must hold to have a greater weight than all the edges in the cycle that 

	  would be created if we added it. Thus, we can just update all the edges of

	  the cycle that haven't been updated and then we just set the weight of 

	  the current non-MST edge with the minimal weight that hasn't been assigned.

	- If we use DSU to join the nodes of the edges that have been labeled by 

	  making the root of the sets a and b the one that has a lower root in the

	  MST, we can just simulate going up until we get to a lower or equal level than

	  the LCA of the nodes.

	- Consider to get the edges to be updated and then update them by increasing

	  index in the order given.

	- In the case of MST-edges, update them directly if they don't have a weight yet.

	- Complexity: O(ElogE)

	- Solution based on original editorial: https://github.com/ranaldmiao/sg_noi_archive/blob/master/2019/solution/NOI_2019_Solution.pdf

*/

const int N = 300000+5;
const int LOG = 20;

int n;
int m;
vi G[N];
vi E[N];
int a[N];
int b[N];
int par[N];
int ans[N];
int mex = 1;
bool vis[N];
int pedge[N];
bool uses[N];
int level[N];
int ST[N][LOG];

void computeLCA(int u, int p){
	ST[u][0] = p;
	for(int d = 1; 1<<d <= level[u]; d++){
		ST[u][d] = ST[p][0];
		p = ST[p][d];
	}
}

void DFS(int u, int p = 0){
	computeLCA(u,p);
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		int e = E[u][i];
		if(v == p) continue;
		pedge[v] = e;
		level[v] = level[u] + 1;
		DFS(v,u);
	}
}

void goUp(int &u, int dis){
	for(int i=LOG-1; i>=0; i--){
		if(dis & (1<<i)){
			u = ST[u][i];
		}
	}
}

int lca(int u, int v){
	if(level[u] < level[v]) swap(u,v);
	goUp(u, level[u] - level[v]);
	if(u == v) return u;
	for(int i=LOG-1; i>=0; i--){
		if(ST[u][i] != ST[v][i]){
			u = ST[u][i];
			v = ST[v][i];
		}
	}
	return ST[u][0];
}

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

void join(int u, int v){
	u = get(u);
	v = get(v);
	if(level[u] < level[v]) swap(u,v);
	par[u] = v;
}

void update(int u, int v){
	int L = lca(u,v);
	vector<int> edges;
	while(level[L] < level[u]){
		if(get(ST[u][0]) == get(u)){
			u = get(u);
		}
		else{
			join(ST[u][0],u);
			edges.emplace_back(pedge[u]);
		}
	}
	while(level[L] < level[v]){
		if(get(ST[v][0]) == get(v)){
			v = get(v);
		}
		else{
			join(ST[v][0],v);
			edges.emplace_back(pedge[v]);
		}
	}
	sort(all(edges));
	for(auto x : edges){
		ans[x] = mex++;
	}
}

int main(){
	ri2(n,m);
	for(int i=1; i<=m; i++){
		ri2(a[i],b[i]);
	}
	for(int i=1; i<n; i++){
		int x;
		ri(x);
		uses[x] = true;
		G[a[x]].emplace_back(b[x]);
		G[b[x]].emplace_back(a[x]);
		E[a[x]].emplace_back(x);
		E[b[x]].emplace_back(x);
	}
	DFS(1);
	for(int i=1; i<=n; i++){
		par[i] = i;
	}
	for(int i=1; i<=m; i++){
		if(ans[i]) continue;
		if(uses[i]){
			ans[i] = mex++;
			join(a[i],b[i]);
		}
		else{
			update(a[i],b[i]);
			ans[i] = mex++;
		}
	}
	for(int i=1; i<=m; i++){
		printf("%d%c",ans[i]," \n"[i == m]);
	}
	return 0;
}
