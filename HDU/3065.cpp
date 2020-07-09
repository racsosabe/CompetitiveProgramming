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

	- Classic Aho-Corasick Automaton problem.

	- Just compute the frecuencies of each node of the automaton and propagate

	  it to its suffix link.

	- To take a correct order the propagating nodes must be visited by non increasing

	  depth (can be sorted using counting sort or normal std::sort).

	- After this process, if you set the terminal node for each pattern, you 

	  can get its frequency in O(1).

	- Complexity: O(n * (log n + |E|) + m), where n is the sum of lengths of the patterns

	  and m is the length of the text.
*/

const int SUML = 1000 * 50 + 3;
const int N = 1000+5;
const int E = 128;

int n;
int nodes;
int pat[N];
int h[SUML];
char s[N][55];
int suf[SUML];
int frec[SUML];
int trie[SUML][E];

void addNode(int u){
	suf[u] = 0;
	for(int i = 0; i < E; i++){
		trie[u][i] = 0;
	}
	frec[u] = 0;
}

void insert(int npat){
	int pos = 0;
	for(int i = 0; s[npat][i]; i++){
		int nxt = s[npat][i];
		if(!trie[pos][nxt]){
			h[nodes] = i + 1;
			addNode(nodes);
			trie[pos][nxt] = nodes++;
		}
		pos = trie[pos][nxt];
	}
	pat[npat] = pos;
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int i = 0; i < E; i++){
			if(trie[u][i]){
				int v = trie[u][i];
				suf[v] = u ? trie[suf[u]][i] : 0;
				Q.emplace(v);
			}
			else{
				trie[u][i] = u ? trie[suf[u]][i] : 0;
			}
		}
	}
}

void buildAutomaton(int npat){
	nodes = 1;
	addNode(0);
	for(int i = 1; i <= npat; i++){
		char c = getchar();
		int pos = 0;
		while(c != '\n'){
			s[i][pos++] = c;
			c = getchar();
		}
		s[i][pos] = '\0';
		insert(i);
	}
	BFS(0);
}

void solve(){
	char c = getchar();
	int state = 0;
	while(c != '\n'){
		state = trie[state][c];
		frec[state] += 1;
		c = getchar();
	}
	vector<int> p(nodes);
	iota(all(p), 0);
	sort(all(p), [&] (int i, int j){
		return h[i] > h[j];
	});
	for(int u : p){
		frec[suf[u]] += frec[u];
	}
}

int main(){
	while(ri(n) == 1){
		getchar();
		buildAutomaton(n);
		solve();
		for(int i = 1; i <= n; i++){
			if(!frec[pat[i]]) continue;
			printf("%s: %d\n", s[i], frec[pat[i]]);
		}
	}
	return 0;
}
