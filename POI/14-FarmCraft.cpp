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

	- Exchange Arguments + DP problem.

	- Try to consider a function memo[u] that will contain the optimal time 

	  to finish the subtree with root u. Obviously, our answer is memo[1].

	- Now, let's notice that the optimal value of memo[u] is related with the

	  order in which we visit the subtrees of the children of u, so we will 

	  try to get an optimal order for that.

	- To compare two children i and j, we need to consider what happens when

	  we go through the subtrees in the order i -> j and j -> i.

	  Let's say that the subtree of i has edges[i] edges and the subtree of j

	  has edges[j] edges.

	  When we go from u to i, we use 1 edge to reach i, then we solve optimally

	  the subtree of u (memo[u]), use 1 edge to return to u, then use 1 edge 

	  to reach j and finally solve optimally the subtree of j and then return to u.

	  Thus, for the order i -> j we have the times:

	  Subtree i: 1 + memo[i]

	  Subtree j: 3 + 2 * edges[i] + memo[j]

	  which will be compared with the total time for the whole subtree of u.

	  Analogously, for the order j -> i we have the times:

	  Subtree j: 1 + memo[j]

	  Subtree i: 3 + 2 * edges[j] + memo[i]

	  So, i goes before j if and only if:

	  max(1 + memo[i], 3 + 2 * edges[i] + memo[j]) < max(1 + memo[j], 3 + 2 * edges[j] + memo[i])

	  Which (analyzing the possible cases) is equivalent to:

	  3 + 2 * edges[i] + memo[j] < 3 + 2 * edges[j] + memo[i]

	  2 * edges[i] - memo[i] < 2 * edges[j] - memo[j]

	- Thus, we have our comparator and we just need to simulate using the optimal

	  order.

	- Complexity: O(nlogn).
*/

const int N = 500000+5;

int n;
vi G[N];
int v[N];
int memo[N];
bool vis[N];
int edges[N];

int DFS(int u){
	vis[u] = true;
	vector<int> children;
	for(int v : G[u]){
		if(vis[v]) continue;
		DFS(v);
		children.emplace_back(v);
		edges[u] += 1 + edges[v];
	}
	sort(all(children),[&](int i, int j){
		return 2 * edges[i] - memo[i] < 2 * edges[j] - memo[j];
	});
	int sum = 0;
	for(int v : children){
		memo[u] = max(memo[u], sum + 1 + memo[v]);
		sum += 2 * edges[v] + 2;
	}
	if(u == 1) memo[u] = max(memo[u], sum + v[u]);
	else memo[u] = max(memo[u], v[u]);
	return memo[u];
}

int main(){
	ri(n);
	for(int i=1; i<=n; i++) ri(v[i]);
	for(int i=1; i<n; i++){
		int u, v;
		ri2(u,v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	printf("%d\n",DFS(1));
	return 0;
}
