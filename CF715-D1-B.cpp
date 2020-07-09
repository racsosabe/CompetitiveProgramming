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

const ll INF = 1e14;
const int N = 1000+5;
const int M = 10000+5;

int n;
int m;
vi G[N];
vi E[N];
ll w[M];
int a[M];
int b[M];
vi special;

ll Dijkstra(int src, int snk){
	vll D(n, INF);
	D[src] = 0;
	priority_queue< pair<ll,int> > Q;
	Q.emplace(mp(0, src));
	while(!Q.empty()){
		int u = Q.top().second;
		ll dis = -Q.top().first;
		Q.pop();
		if(D[u] < dis) continue;
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			int e = E[u][i];
			ll we = w[e];
			assert(we >= 0);
			if(!we) continue;
			if(D[v] > D[u] + we){
				D[v] = D[u] + we;
				Q.emplace(mp(-D[v], v));
			}
		}
	}
	return D[snk];
}

void fixEdges(int l){
	for(int i=0; i<special.size(); i++){
		if(i < l) w[special[i]] = 1;
		else w[special[i]] = INF;
	}
}

int main(){
	ri2(n, m);
	int L, s, t;
	ri3(L, s, t);
	for(int i=0; i<m; i++){
		ri2(a[i], b[i]);
		rll(w[i]);
		if(!w[i]){
			special.emplace_back(i);
		}
		G[a[i]].emplace_back(b[i]);
		G[b[i]].emplace_back(a[i]);
		E[a[i]].emplace_back(i);
		E[b[i]].emplace_back(i);
	}
	if(Dijkstra(s, t) < L){
		puts("NO");
		return 0;
	}
	for(int i : special) w[i] = 1;
	if(Dijkstra(s, t) > L){
		puts("NO");
		return 0;
	}
	if(!special.empty()){
		int lo = 1, hi = special.size();
		while(lo < hi){
			int mi = lo + (hi - lo) / 2;
			fixEdges(mi);
			if(Dijkstra(s, t) > L) lo = mi + 1;
			else hi = mi;
		}
		ll low = 1, hiw = INF;
		fixEdges(lo);
		while(low < hiw){
			ll mi = low + (hiw - low) / 2;
			w[special[lo-1]] = mi;
			if(Dijkstra(s, t) < L) low = mi + 1;
				else hiw = mi;
		}
		w[special[lo-1]] = low;
		assert(Dijkstra(s, t) == L);
	}
	if(Dijkstra(s, t) != L){
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=0; i<m; i++){
		printf("%d %d %lld\n", a[i], b[i], w[i]);
	}
	return 0;
}
