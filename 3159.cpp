#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<utility>
#include<algorithm>
#include<cmath>
#include<queue>
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

const int N = 30000+5;
const int E = 150000+5;
const int inf = 1<<30;

int n;
int m;
int len;
int D[N];
int W[E];
int to[E];
int nxt[E];
int last[N];

void addEdge(int i, int j, int w){
	// j -> i
	W[len] = w;
	to[len] = i;
	nxt[len] = last[j];
	last[j] = len;
	len += 1;
}

int Dijkstra(int src){
	for(int i=1; i<=n; i++) D[i] = inf;
	D[src] = 0;
	priority_queue< pair<ll,int> > Q;
	Q.push(mp(0, src));
	while(!Q.empty()){
		ll dis = -Q.top().first;
		int u = Q.top().second;
		Q.pop();
		if(D[u] < dis) continue;
		for(int e=last[u]; e != -1; e = nxt[e]){
			int v = to[e];
			int w = W[e];
			if(D[v] > D[u] + w){
				D[v] = D[u] + w;
				Q.push(mp(-D[v],v));
			}
		}
	}
	return D[n];
}

int main(){
	ri2(n, m);
	len = 0;
	memset(last, -1, sizeof last);
	for(int i=1; i<=m; i++){
		int a, b, w;
		ri3(a, b, w);
		addEdge(b, a, w);
	}
	printf("%d\n",Dijkstra(1));
	return 0;
}
