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

	- If we consider the two disjoint paths, then the set of vertices can be

	  partitioned into two components such that each of them contains one of the

	  paths.

	- Thus, if we consider the two components formed by erasing one edge, we just 

	  need to find the longest paths on both of them and multiply those answers.

	- We can just iterate over all the edges and build the corresponding graph

	  ignoring it.

	- Complexity: O(n^2), the longest path can also be found by using 2 BFS, but YOLO

*/

const int N = 200+5;

int n;
vi G[N];
int h[N];
vii edges;
int memo[N];

int DP(int u, int p = -1){
	for(int v : G[u]){
		if(v == p) continue;
		memo[u] = max(memo[u], DP(v, u));
		h[u] = max(h[u], 1 + h[v]);
	}
	memo[u] = max(memo[u], h[u]);
	int maxH = -2;
	for(int v : G[u]){
		if(v == p) continue;
		memo[u] = max(memo[u], 2 + maxH + h[v]);
		maxH = max(maxH, h[v]);
	}
	return memo[u];
}

int solve(int pos){
	for(int i=1; i<=n; i++){
		G[i].clear();
		memo[i] = 0;
		h[i] = 0;
	}
	for(int i=0; i<edges.size(); i++){
		if(i == pos) continue;
		int u = edges[i].first, v = edges[i].second;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	int u = edges[pos].first;
	int v = edges[pos].second;
	return DP(u) * DP(v);
}

int main(){
	ri(n);
	for(int i=1; i<n; i++){
		int u, v;
		ri2(u,v);
		edges.emplace_back(mp(u, v));
	}
	int ans = 0;
	for(int i=0; i<edges.size(); i++){
		ans = max(ans, solve(i));
	}
	printf("%d\n",ans);
	return 0;
}
