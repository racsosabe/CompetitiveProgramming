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

const int N = 1000+5;
const int M = 30000+5;
const int inf = 2e9 + 5;

int n;
int m;
int Timestamp;
vi G[N];
vi E[N];
vi T[N];
vi TE[N];
int a[M];
int b[M];
int w[M];
int p[M];
int tin[N];
int low[N];
int comp[N];
bool vis[N];
bool vis2[N];
bool bridge[M];
int ignored = 0;
 
void DFS(int u, int p = -1){
	vis[u] = true;
	low[u] = tin[u] = Timestamp++;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int e = E[u][i];
		if(e == ignored or v == p) continue;
		if(vis[v]){
			low[u] = min(low[u], tin[v]);
		}
		else{
			DFS(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > tin[u]){
				bridge[e] = true;
			}
		}
	}
}
 
ii test(int s, int t){
	for(int i=1; i<=n; i++) vis[i] = vis2[i] = false;
	for(int i=1; i<=m; i++){
		bridge[i] = false;
	}
	Timestamp = 0;
	DFS(s);
	if(!vis[t]) return mp(ignored, inf);
	int len = 0;
	vi nxt(1, s);
	while(!nxt.empty()){
		int u = nxt.back();
		nxt.pop_back();
		if(vis2[u]) continue;
		vi Q;
		Q.emplace_back(u);
		vis2[u] = true;
		comp[u] = len;
		while(!Q.empty()){
			int u = Q.back();
			Q.pop_back();
			for(int i = 0; i < G[u].size(); i++){
				int v = G[u][i];
				int e = E[u][i];
				if(vis2[v] or e == ignored) continue;
				if(bridge[e]){
					nxt.emplace_back(v);
					continue;
				}
				Q.emplace_back(v);
				comp[v] = len;
				vis2[v] = true;
			}
 
		}
		len += 1;
	}
	if(comp[s] == comp[t]) return mp(inf, inf);
	for(int i = 1; i <= m; i++){
		int x = p[i];
		if(!vis[a[x]] or !vis[b[x]] or x == ignored) continue;
		int ca = comp[a[x]];
		int cb = comp[b[x]];
		if(ca != cb){
			T[ca].emplace_back(cb);
			TE[ca].emplace_back(x);
			T[cb].emplace_back(ca);
			TE[cb].emplace_back(x);
		}
	}
	for(int i=0; i<len; i++) vis2[i] = false;
	queue<ii> Q;
	Q.emplace(mp(comp[s], inf));
	ii res;
	while(!Q.empty()){
		int u = Q.front().first;
		int pe = Q.front().second;
		Q.pop();
		if(u == comp[t]){
			res = mp(ignored, pe);
			break;
		}
		for(int i = 0; i < T[u].size(); i++){
			int v = T[u][i];
			int e = TE[u][i];
			if(vis2[v]) continue;
			int new_e = pe == inf? e : (w[e] < w[pe]? e : pe);
			Q.emplace(mp(v, new_e));
			vis2[v] = true;
		}
	}
	for(int i=0; i<len; i++) T[i].clear(), TE[i].clear();
	return res;
}

int getAns(ii x){
	if(x.first == inf) return inf;
	return (x.first != inf? w[x.first] : 0) + (x.second != inf? w[x.second] : 0);
}

int validEdge(int x){
	return 0 <= x and x <= m;
}

void printAnswer(vi &v){
	int sum = 0;
	for(auto x : v) sum += w[x];
	printf("%d\n%d\n", sum, (int)v.size());
	for(int i=0; i<v.size(); i++){
		printf("%d%c", v[i], " \n"[i + 1 == v.size()]);
	}
}

vi getPath(int s, int t){
	vector<bool> visited(n + 1, false);
	vector<int> pedge(n + 1, -1);
	vector<int> pnode(n + 1, -1);
	queue<int> Q;
	Q.emplace(s);
	vis[s] = true;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			int e = E[u][i];
			if(visited[v]) continue;
			pedge[v] = e;
			pnode[v] = u;
			visited[v] = true;
			Q.emplace(v);
		}
	}
	if(!visited[t]) return {0};
	vi ans;
	while(t != s){
		ans.emplace_back(pedge[t]);
		t = pnode[t];
	}
	return ans;
}

int main(){
	int s, t;
	ri2(n, m);
	ri2(s, t);
	for(int i=1; i<=m; i++){
		p[i] = i;
		ri3(a[i], b[i], w[i]);
		E[a[i]].emplace_back(i);
		E[b[i]].emplace_back(i);
		G[a[i]].emplace_back(b[i]);
		G[b[i]].emplace_back(a[i]);
	}
	sort(p + 1, p + 1 + m, [&] (int i, int j){
		return w[i] < w[j];
	});
	ii ans = test(s, t);
	vi path = getPath(s, t);
	for(auto e : path){
		ignored = e;
		ii cur = test(s, t);
		if(getAns(cur) < getAns(ans)){
			ans = cur;
		}
	}
	if(!validEdge(ans.first)){
		puts("-1");
		return 0;
	}
	vi res;
	if(validEdge(ans.first) and ans.first) res.emplace_back(ans.first);
	if(validEdge(ans.second) and ans.second) res.emplace_back(ans.second);
	printAnswer(res);
	return 0;
}
