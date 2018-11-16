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
		- Nice Graph Transformation problem

		- First of all, let's get a new tree

		  G from the original tree T such that

		  a connected component of the same color

		  in T is only one node in G.

		- Now, we notice that if we choose any 

		  vertex u in G to start painting, we will

		  end in t operations, where t is

		  max(D[v]) for each v in T.

		- We have changed our problem to the following:

		  "Find the vertex such that the maximum distance
		  
		  from it to any other node is minimized".

		  In graph theory, this is the definition of the

		  center of a graph.

		- Finally, just find the center and get the maximum

		  distance to any node and that will be our answer.

		- Complexity: O(nlogn), mainly for Tree transformation.
*/

const int N = 200000+5;

int n;
int c[N];
vi T[N];
vi G[N];
int comp[N];
vii edges;
int compno;
int C;

void readData(){
	ri(n);
	for(int i=1; i<=n; i++){
		ri(c[i]);
	}
	int a,b;
	for(int i=1; i<n; i++){
		ri2(a,b);
		T[a].pb(b);
		T[b].pb(a);
		edges.pb(mp(a,b));
	}
}

void DFS(int u, int cno){
	comp[u] = cno;
	for(int i=0; i<T[u].size(); i++){
		int v = T[u][i];
		if(c[u] != c[v] or comp[v]) continue;
		DFS(v,cno);
	}
}

void getNewGraph(){
	compno = 1;
	for(int i=1; i<=n; i++){
		if(!comp[i]){
			DFS(i,compno++);
		}
	}
	compno--;
	int a,b;
	int u,v;
	set<ii> new_edges;
	for(int i=0; i<n-1; i++){
		a = edges[i].first;
		b = edges[i].second;
		if(comp[a] == comp[b]) continue;
		u = comp[a];
		v = comp[b];
		if(u > v) swap(u,v);
		new_edges.insert(mp(u,v));
	}
	for(set<ii>::iterator it=new_edges.begin(); it!=new_edges.end(); it++){
		ii act = *it;
		G[act.first].pb(act.second);
		G[act.second].pb(act.first);
	}
}

void getCenter(){
	int len = compno;
	int in[N];
	bool vis[N];
	queue<int> Q;
	for(int i=1; i<=compno; i++){
		in[i] = G[i].size();
		vis[i] = false;
		if(in[i] == 1){
			Q.push(i);
		}
	}
	while(len >= 2 and !Q.empty()){
		int u = Q.front(); Q.pop();
		vis[u] = true;
		len--;
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(!vis[v]){
				in[v]--;
				if(in[v] == 1){
					Q.push(v);
				}
			}
		}
	}
	for(int i=1; i<=compno; i++){
		if(!vis[i]) C = i;
	}
}

void getMostDistant(int &ans){
	int D[N];
	for(int i=1; i<=compno; i++){
		D[i] = INT_MAX;
	}
	D[C] = 0;
	queue<int> Q;
	Q.push(C);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			if(D[v] > D[u] + 1){
				D[v] = D[u] + 1;
				Q.push(v);
			}
		}
	}
	ans = C;
	for(int i=1; i<=compno; i++){
		if(D[i] == INT_MAX) continue;
		if(D[i] > D[ans]) ans = i;
	}
	ans = D[ans];
}

int main(){
	readData();
	getNewGraph();
	int ans;
	getCenter();
	getMostDistant(ans);
	printf("%d\n",ans);
	return 0;
}
