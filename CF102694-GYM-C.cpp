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

const int N = 300000+5;
const int LOG = 20;

int n;
int q;
vi G[N];
int h[N];
int ST[N][LOG];

void computeLCA(int u, int p){
	ST[u][0] = p;
	for(int d = 1; 1<<d <= h[u]; d++){
		ST[u][d] = ST[p][0];
		p = ST[p][d];
	}
}

void DFS(int u, int p = -1){
	computeLCA(u, p);
	for(int v : G[u]){
		if(v == p) continue;
		h[v] = h[u] + 1;
		DFS(v, u);
	}
}

void goUp(int &a, int dis){
	for(int i = LOG-1; i >= 0; i--){
		if(dis & (1<<i)){
			a = ST[a][i];
		}
	}
}

int lca(int a, int b){
	if(h[a] < h[b]) swap(a, b);
	goUp(a, h[a] - h[b]);
	if(a == b) return a;
	for(int i = LOG - 1; i >= 0; i--){
		if(ST[a][i] != ST[b][i]){
			a = ST[a][i];
			b = ST[b][i];
		}
	}
	return ST[a][0];
}

int solve(int a, int b, int c){
	int l = lca(a, b);
	if(c >= h[a] + h[b] - 2 * h[l]) return b;
	if(c > h[a] - h[l]){
		c -= h[a] - h[l];
		goUp(b, h[b] - h[l] - c);
		return b;
	}
	else{
		goUp(a, c);
		return a;
	}
}

int main(){
	ri(n);
	for(int i = 1; i < n; i++){
		int u, v;
		ri2(u, v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(1);
	ri(q);
	while(q--){
		int a, b, c;
		ri3(a, b, c);
		printf("%d\n", solve(a, b, c));
	}
	return 0;
}
