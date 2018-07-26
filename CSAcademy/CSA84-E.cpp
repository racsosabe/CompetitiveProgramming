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

		- Ternary Search & Trees problem. Important use of convex functions.

		- Let's say that a function F(P,t) is the length of the path P

		  at the t-th day, so we notice that:

		  F(P,t) = F(P,0) + \sum\limits_{i=1}^{k}A_{p_{i}}*t 

		  Given that p_{i} is the id of the i-th edge in the path.

		  We notice that it is a linear function with t as variable.

		  Also, we need to take the maximum for all the paths, and the

		  Max function is convex.
		  Proof: https://math.stackexchange.com/questions/2435464/show-that-max-function-on-rn-is-convex

		- Create a DFS like function to get the two longest paths from the node
		  to any children, maximize for each node and that will get the diameter.
*/

const int N = 250000+5;

int n,d;
int u[N];
int v[N];
int A[N];
int C[N];
viii G[N];
ll act_diameter;

ll longest_path(int u, int p, int t){ // Gives the longest path from this node to any children
	ll Fmax = 0LL;
	ll Smax = 0LL;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i].first;
		if(v == p) continue;
		ll c = G[u][i].second.first;
		ll a = G[u][i].second.second;
		ll weight = c + a*t;
		ll candidate = longest_path(v,u,t) + weight;
		if(candidate > Smax){
			Smax = candidate;
		}
		if(Fmax < Smax) swap(Fmax,Smax);
	}
	act_diameter = max(act_diameter,Fmax+Smax);
	return Fmax;
}

ll solve(int t){ // Gives the diameter for the day t
	act_diameter = 0;
	ll dump = longest_path(1,0,t);
	return act_diameter;
}

int main(){
	ri2(n,d);
	for(int i=0; i<n-1; i++){
		ri2(u[i],v[i]);
		ri2(C[i],A[i]);
		G[u[i]].pb(mp(v[i],mp(C[i],A[i])));
		G[v[i]].pb(mp(u[i],mp(C[i],A[i])));
	}
	int lo = 0, hi = d-1;
	while(lo <= hi){
		int mi = lo + (hi-lo)/2;
		ll L = solve(mi);
		ll R = solve(mi+1);
		if(L <= R) hi = mi-1;
		else lo = mi+1;
	}
	printf("%d\n%lld\n",lo,solve(lo));
	return 0;
}
