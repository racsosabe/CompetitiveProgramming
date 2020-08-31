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

const int N = 100000+5;

int n;
int m;
int k;
vi G[N];
int ans;
int D[N];
vi special;
bool vis[N];

bool BFS(int src){
	for(int i = 1; i <= n; i++) D[i] = -1;
	D[src] = 0;
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			if(D[v] != -1) continue;
			D[v] = D[u] + 1;
			Q.emplace(v);
		}
	}
	bool found = false;
	for(int i = 0; i < k; i++){
		if(special[i] != src and ans > D[special[i]]){
			ans = D[special[i]];
			found = true;
		}
	}
	return found;
}

int solve(){
	ans = n + 1;
	int src = 0;
	vis[0] = true;
	while(BFS(special[src])){
		int furthest = -1;
		vis[src] = true;
		for(int i = 0; i < k; i++){
			if(vis[i]) continue;
			if(furthest == -1 or D[special[furthest]] < D[special[i]]) furthest = i;
		}
		src = furthest;
	}
	return ans;
}

int main(){
	freopen("reinvent.in", "r", stdin);
	freopen("reinvent.out", "w", stdout);
	ri3(n, m, k);
	for(int i = 1; i <= m; i++){
		int u, v;
		ri2(u, v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for(int i = 0; i < k; i++){
		int x;
		ri(x);
		special.emplace_back(x);
	}
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
