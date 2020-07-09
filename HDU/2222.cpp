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

	- Basic Aho-Corasick problem.

	- Just notice that if we build the automaton and try to update the occurrences

	  of some state X, then we must update all its suffix links recursively.

	  So, since we cannot repeat occurrences, we can just use a visited boolean

	  array to mark a state so we can count only the ones that haven't been visited 

	  yet.

	- Complexity: O(n * |E| + m) per case, where n is the sum of lengths of the

	  patterns, E is the alphabet and m is the length of the text.

*/

const int SUML = 500000 + 5;
const int E = 26;

int n;
int nodes;
char s[55];
int cnt[SUML];
int suf[SUML];
bool vis[SUML];
bool used[SUML];
int go[SUML][E];
int trie[SUML][E];

void insert(int npat){
	int pos = 0;
	for(int i = 0; s[i]; i++){
		int nxt = s[i] - 'a';
		if(trie[pos][nxt] == 0){
			cnt[nodes] = 0;
			for(int j = 0; j < E; j++) trie[nodes][j] = go[nodes][j] = 0;
			trie[pos][nxt] = nodes++;
		}
		pos = trie[pos][nxt];
	}
	cnt[pos] += 1;
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for(int i = 0; i < E; i++){
			if(!trie[u][i]){
				go[u][i] = u ? go[suf[u]][i] : 0;
			}
			else{
				go[u][i] = trie[u][i];
			}
		}
		for(int i = 0; i < E; i++){
			if(trie[u][i]){
				int v = trie[u][i];
				suf[v] = u? go[suf[u]][i] : 0;
				Q.emplace(v);
			}
		}
	}
}

void buildAutomaton(int npat){
	nodes = 1;
	suf[0] = 0;
	cnt[0] = 0;
	for(int i = 0; i < E; i++) trie[0][i] = go[0][i] = 0;
	for(int i = 1; i <= npat; i++){
		scanf("%s", s);
		insert(i);
	}
	BFS(0);
}

int propagate(int state){
	if(vis[state]) return 0;
	if(state == 0) return 0;
	int ans = cnt[state];
	ans += propagate(suf[state]);
	vis[state] = true;
	return ans;
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri(n);
		buildAutomaton(n);
		getchar();
		ll ans = 0LL;
		int state = 0;
		char c = getchar();
		int pos = 0;
		while(c != '\n'){
			int nxt = c - 'a';
			int nstate = go[state][nxt];
			ans += propagate(nstate);
			state = nstate;
			pos += 1;
			c = getchar();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
