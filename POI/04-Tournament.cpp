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

	- TopoSort problem.

	- First, notice that all the possible winners must beat all the losers.

	  This can be proved by contradiction by assuming that there exists a winner

	  u that doesn't beat a loser v. Then, we can take any instance of the tournament

	  in which u wins and remove the match in which v lost. Let w be the one 

	  who beat v in that match, then there are 2 possibilities:

	  1) w is u, in which case we are left with 2 programs and we can make v beat

	     u since that possibility exists.

	  2) w is another program that will be eventually beaten by another one, so

	     we are left again with 2 programs and we can make v win again.

	- Thus, we need to find a set W such that all its nodes have edges to all the

	  nodes in V \ W (say L).

	- We can use a Topological sort of the SCCs and the set W will be a prefix

	  of that order. This happens because of the nature of topological order:

	  the suffix will probably have its incoming edges from the prefix.

	- We don't actually need to get the SCCs, since the existence of both paths

	  from a node u to v and viceversa will be reflected by the edges from W to L.

	- Complexity: O(n + m)
*/

const int N = 100000+5;

int n;
int T;
vi G[N];
int in[N];
int ans[N];
bool vis[N];
int order[N];

void DFS(int u){
	vis[u] = true;
	for(int v : G[u]){
		if(vis[v]) continue;
		DFS(v);
	}
	order[T++] = u;
}

void TopoSort(){
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		DFS(i);
	}
}

int main(){
	ri(n);
	for(int i = 1; i <= n; i++){
		int q;
		ri(q);
		for(int j = 0; j < q; j++){
			int x;
			ri(x);
			G[i].emplace_back(x);
		}
	}
	TopoSort();
	reverse(order, order + T);
	for(int i = 1; i <= n; i++) vis[i] = false;
	int out = 0;
	T = 0;
	for(int i = 0; i < n; i++){
		int u = order[i];
		ans[T++] = u;
		out -= in[u];
		vis[u] = true;
		for(int v : G[u]){
			if(vis[v]) continue;
			out += 1;
			in[v] += 1;
		}
		if(out == 1LL * T * (n - T)) break;
	}
	printf("%d", T);
	sort(ans, ans + T);
	for(int i = 0; i < T; i++){
		printf(" %d", ans[i]);
	}
	putchar('\n');
	return 0;
}
