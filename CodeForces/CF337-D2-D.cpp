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

ll add(ll a, ll b, ll m = MOD){ return (a%m + b%m+2*m)%m;}

ll mul(ll a, ll b, ll m = MOD){ return ((a%m+m)*(b%m+m))%m;}

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
		- Nice DP on Trees problem.

		- The main idea is to find the number of vertices that have a max
		  distance from any marked vertex <= d.

		- Let's define 2 functions:

			* max_subtree[u]: gives the maximum distance of u to a marked
			  vertex in the subtree of which u is root.

			* max_outside[u]: gives the maximum distance of u to a marked
			  vertex outside the subtree of which u is root.
		  
		  Now we see that max_outside can be computed from max_subtree, so

		  let's notice that:

		  max_subtree[u] = max(max_subtree[vi]+1), where vi is a child of u

		  max_subtree[leaf] = - inf if it's not marked or 0 if it is.

		  Finally, let's see that max_outside[u] can be computed from

		  siblings and the parent:

		  The only vertices outside u's subtree are:

		  	* u's siblings subtrees
			* u's parent outsiders
		  
		  So, we have:

		  max_outside[u] = max_outside[p] + 1 as first try

		  Then, for each sibling:

		  max_outside[u] = max(max_outside[u],max_subtree[sib]+2)

		  The +1 is to reach u from parent and +2 is to reach u from a sibling.
		  
		  Finally, get the number of vertices such that 
		  
		  max(max_subtree[u],max_outside[u]) <= d

		  When computing max from siblings, just take 2 maximum values of all siblings

		  and if maximum == max_subtree[u] then use second maximum, else use

		  the original maximum.

		- Complexity: O(V+E) = O(n) since it's a tree.
*/


const int N = 100000+5;

int n,m,d;
vi G[N];
bool is[N];
int max_subtree[N];
int max_outside[N];

void DFS1(int u, int p){
	max_subtree[u] = is[u]?0:-1;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(v!=p){
			DFS1(v,u);
			if(max_subtree[v] >= 0) 
				max_subtree[u] = max(max_subtree[u],max_subtree[v]+1);
		}
	}
}

void DFS2(int u, int p){ // Propagate max_outside for all children
	// Get two max values
	int max1 = -1;
	int max2 = -1;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(v == p) continue;
		if(max1 < max_subtree[v]){
			max2 = max1;
			max1 = max_subtree[v];
		}
		else if(max2 < max_subtree[v]) max2 = max_subtree[v];
	}
	// Update max_outside for each one
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(v == p) continue;
		max_outside[v] = is[v]?0:-1;
		if(max_outside[u] >= 0){
			max_outside[v] = max(max_outside[v],max_outside[u]+1);
		}
		if(max_subtree[v] == max1){
			if(max2 >= 0){
				max_outside[v] = max(max_outside[v],max2+2);
			}
		}
		else{
			if(max1 >= 0){
				max_outside[v] = max(max_outside[v],max1+2);
			}
		}
	}
	// Propagate to each child
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(v == p) continue;
		DFS2(v,u);
	}
}

int main(){
	int x;
	ri3(n,m,d);
	for(int i=0; i<m; i++){
		ri(x);
		is[x] = true;
	}
	int a,b;
	for(int i=0; i<n-1; i++){
		ri2(a,b);
		G[a].pb(b);
		G[b].pb(a);
	}
	DFS1(1,0);
	max_outside[1] = is[1]?0:-1;
	DFS2(1,0);
	int ans = 0;
	for(int i=1; i<=n; i++){
		if(max_subtree[i] <= d and max_outside[i] <= d){
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
