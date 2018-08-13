#include<iostream>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
#include<map>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<stack>
#include<cstring>
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
		- Good Trie + Trees problem.

		- We need the maximum xor sum path from all possible ones in tree
		  So, let's claim that if we already have a partial path, we can get the 
		  value that maximizes the overall xor sum of the final path in a
		  fast way.

		- Now, let's say that we have randomly assigned a root vertex to

		  the tree.

		  So, if we define f(p) as the xor sum of all edges from the path p

		  then, we need to find:

		  ans = max(f(u,v)) for all 1 <= u,v <= n

		  but we know that:

		  ans = max(f(u,v) = f(u,LCA(u,v)) XOR f(LCA(u,v),v))

		  And since we are using XOR and A XOR A = 0

		  ans = max(f(u,v) = f(u,LCA(u,v)) XOR f(LCA(u,v),v) XOR f(root,LCA(u,v)) XOR f(root,LCA(u,v)))

		  we can adjust it to:

		  ans = max(f(u,v) = f(root,u) XOR f(root,v))

		  And since we have claimed that if we have f(p) we can get it's maximizer

		  fast enough, we can fix f(root,u) and just get it with it.

		- To get the maximizer we can use a trie for maximizing XOR of two values
		  which is a typical problem.

		- Complexity: O(V+E+VlogMAX) = O(VlogMAX) since it's a tree and the log
		
		  factor is because of the trie (length of string).

		- Note: Strict Time Limit, had to use a special way of storing graph
		  edges instead of vector or any other way.

*/

const int N = 100000;
const int E = 2;
const int L = 32;
const int OFFSET = 2;
const int EDGE = 2*N;

int n;
int nodos = 1;
int arista = 0;
bool vis[N+OFFSET];
int in[EDGE+OFFSET];
int peso[EDGE+OFFSET];
int before[EDGE+OFFSET];
int last[N+OFFSET];
ll path_to[N+OFFSET];
int trie[N*L+OFFSET][E+OFFSET];

void insert(int x){
	int pos = 0;
	for(int i=31; i>=0; i--){
		int next = (x>>i)&1;
		if(trie[pos][next]==0){
			trie[pos][next] = nodos++;
			for(int j=0; j<E; j++){
				trie[nodos-1][j] = 0;
			}
		}
		pos = trie[pos][next];
	}
}

int getMaximizer(int x){
	int ans = 0;
	int pos = 0;
	for(int i=31; i>=0; i--){
		int wanted = !((x>>i)&1);
		if(trie[pos][wanted]){
			ans ^= (1<<i);
		}
		else{
			wanted ^= 1;
		}
		pos = trie[pos][wanted];
	}
	return ans;
}

void edge(int u, int v, int w){
	// u -> v
	in[arista] = v;
	peso[arista] = w;
	before[arista] = last[u];
	last[u] = arista++;
	// v -> u
	in[arista] = u;
	peso[arista] = w;
	before[arista] = last[v];
	last[v] = arista++;
}


int main(){
	while(ri(n)==1){
		int a,b,w;
		memset(last,-1,sizeof last);
		memset(vis,0,sizeof vis);
		arista = 0;
		for(int i=1; i<n; i++){
			ri3(a,b,w);
			edge(a,b,w);
		}
		nodos = 1;
		for(int i=0; i<E; i++) trie[0][i] = 0;
		stack<int> S;
		S.push(0);
		S.push(0);
		while(!S.empty()){
			int u = S.top(); S.pop();
			int XOR = S.top(); S.pop();
			insert(XOR);
			path_to[u] = XOR;
			for(int i=last[u]; i!=-1; i=before[i]){
				int v = in[i];
				int w = peso[i];
				if(!vis[v]){
					vis[v] = true;
					S.push(XOR^w);
					S.push(v);
				}
			}
		}
		int ans = 0;
		for(int i=0; i<n; i++){
			ans = max(ans,getMaximizer(path_to[i]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
