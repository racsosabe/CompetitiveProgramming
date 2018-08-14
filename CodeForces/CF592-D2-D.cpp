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
		- Nice Trees problem.

		- First, we need to start in one of the cities to get the minimum.
		  Now, we can see that the set of attacked cities can be contained in a subtree

		  so we get the minimum subtree that works. We do that with a DFS

		  that says:

		  DFS(u,p) states if the path from root to u is needed to contain the cities

		  So, we see that:

		  DFS(u) = true if u is an attacked city or any of its children is
		  And to get the correct subtree we start in an attacked city as root.

		- Once we have gotten the subtree T, we see that our answer is:

		  2E - (Longest path in subtree)

		  So, to minimize the time we need to maximize the longest path but
		  also minimizing the two ends of it.

		- Therefore, we need to find the center of T and get the two vertices such that
		  the path between them is a diameter and one of the vertices has
		  minimal id.

		- Complexity: O(V+E) = O(n)
*/

const int N = 123456;
const int OFFSET = 2;

int n,m;
vi centers;
int D[N+OFFSET];
int nodes_subtree;
bool attacked[N+OFFSET];
vi G[N+OFFSET], T[N+OFFSET];

bool DFS(int u, int p){
	// States if path from root to u is needed
	// for subtree T
	bool needed = attacked[u];
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(v!=p){
			if(DFS(v,u)){
				needed = true;
				T[u].pb(v);
				T[v].pb(u);
			}
		}
	}
	return needed;
}

void getCenter(){
	// Get Center of a Tree
	queue<int> Q;
	int max_level = 0;
	int degree[N+OFFSET];
	int level[N+OFFSET];
	// Add leaves to queue
	for(int i=1; i<=n; i++){
		degree[i] = T[i].size();
		level[i] = T[i].size()?0:-1;
		if(degree[i] == 1) Q.push(i);
	}
	// Continuously take off leaves until
	// <= 2 remaining, for this consider
	// max_level as the center's level
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		for(int i=0; i<T[u].size(); i++){
			int v = T[u][i];
			degree[v]--;
			if(degree[v] == 1){
				Q.push(v);
				level[v] = level[u]+1;
				max_level = max(max_level,level[v]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(T[i].size() and level[i] == max_level){
			centers.pb(i);
		}
	}
}

void BFS(int source, int avoid, vii &a){
	// Gets distances from vertices without avoid subtree.
	// Add to a pairs {Distance, Vertex} from attacked cities
	D[source] = 0;
	queue<int> Q;
	Q.push(source);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		if(attacked[u]) a.pb(mp(D[u],u));
		nodes_subtree++;
		for(int i=0; i<T[u].size(); i++){
			int v = T[u][i];
			if(v == avoid) continue;
			if(D[v] > D[u]+1){
				D[v] = D[u]+1;
				Q.push(v);
			}
		}
	}
}

bool comp(ii a, ii b){
	if(a.first > b.first) return true;
	if(a.first < b.first) return false;
	return a.second < b.second;
}

int main(){
	ri2(n,m);
	int a,b;
	for(int i=1; i<n; i++){
		ri2(a,b);
		G[a].pb(b);
		G[b].pb(a);
	}
	for(int i=0; i<m; i++){
		ri(a);
		attacked[a] = true;
	}
	if(m == 1){
		cout << a << endl << 0 << endl;
	}
	else{
		bool dump = DFS(a,0);
		getCenter();
		int ans,pos;
		for(int i=1; i<=n; i++) D[i] = n<<1;
		if(centers.size()==1){
			// Take 2 longest from center and join them
			vii Distances;
			BFS(centers[0],0,Distances);
			sort(all(Distances),comp);
			pos = min(Distances[0].second,Distances[1].second);
			ans = 2*(nodes_subtree-1) - Distances[0].first - Distances[1].first;
		}
		else{
			// Take longest from each center and join them
			vii Distances1, Distances2;
			int c0 = centers[0], c1 = centers[1];
			BFS(c0,c1,Distances1);
			BFS(c1,c0,Distances2);
			sort(all(Distances1),comp);
			sort(all(Distances2),comp);
			pos = min(Distances1[0].second,Distances2[0].second);
			ans = 2*(nodes_subtree-1) - Distances1[0].first - Distances2[0].first - 1;
		}
		printf("%d\n%d\n",pos,ans);
	}
	return 0;
}
