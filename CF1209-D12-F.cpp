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

int add(int a, int b, int m = MOD){
	return (a + b) % m;
}

int mul(ll a, ll b, int m = MOD){
	return (a * b) % m;
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

const int MAX = 1e6 + 5;

int n;
int m;
int nodes;
vii G[MAX];
int D[MAX];
int p[MAX];
int pa[MAX];
int val[MAX];
int res[MAX];
vector<ii> frontier, new_frontier;

void process(int pos, int l, int r){
	vector<int> v;
	for(int x = pos; x > 0; x /= 10) v.emplace_back(x % 10);
	reverse(all(v));
	int par = l;
	for(int i = 0; i + 1 < v.size(); i++){
		G[par].emplace_back(mp(nodes, v[i]));
		par = nodes;
		nodes += 1;
	}
	G[par].emplace_back(mp(r, v.back()));
}

void useDigit(int L, int R, int d){
	for(int i = L; i < R; i++){
		int u = frontier[i].first;
		while(!G[u].empty() and G[u].back().second == d){
			int v = G[u].back().first;
			if(D[v] == -1){
				p[v] = d;
				pa[v] = u;
				D[v] = D[u] + 1;
				res[v] = add(mul(10, res[u]), d);
				if(new_frontier.empty()) val[v] = 0;
				else{
					int last = new_frontier.back().first;
					if(mp(val[pa[last]], p[last]) == mp(val[u], d)){
						val[v] = new_frontier.back().second;
					}
					else{
						val[v] = new_frontier.back().second + 1;
					}
				}
				new_frontier.emplace_back(mp(v, val[v]));
			}
			G[u].pop_back();
		}
	}
}

void insert(int L, int R){
	for(int d = 0; d < 10; d++){
		useDigit(L, R, d);
	}
}

void BFS(int src){
	for(int i=1; i<nodes; i++){
		D[i] = -1;
		res[i] = 0;
	}
	D[src] = 0;
	p[src] = 0;
	val[src] = 0;
	res[src] = 0;
	frontier.emplace_back(mp(src, 0));
	while(!frontier.empty()){
		new_frontier.clear();
		int L = 0, R = 0;
		while(L < frontier.size()){
			while(R < frontier.size() and frontier[L].second == frontier[R].second) R += 1;
			insert(L, R);
			L = R;
		}
		swap(frontier, new_frontier);
	}
}

int main(){
	ri2(n, m);
	nodes = n + 1;
	for(int i=1; i<=m; i++){
		int u, v;
		ri2(u, v);
		process(i, u, v);
		process(i, v, u);
	}
	for(int i=1; i<nodes; i++){
		sort(all(G[i]), [&](ii a, ii b){
			return a.second > b.second;
		});
	}
	BFS(1);
	for(int i=2; i<=n; i++){
		printf("%d\n", res[i]);
	}
	return 0;
}
