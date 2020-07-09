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
const int MOD = 20090717;

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
	return a + b < m? a + b : a + b - m;
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

	- Classic Aho-Corasick Automaton + DP problem

	- Just build the automaton and use it inside the DP.

	- We will use a recursion:

	  DP(pos, state, mask) : The number of ways to build a string with length "pos"

	  given that we are currently in state "state" and we have already as substrings

	  the patterns in the mask.

	- A little optimization over the direct DP is to consider that the states

	  form a DAG and our answer is just the number of paths from (0, 0, 0) to 

	  the states so we can use a BFS over the states.

	- Complexity: O(n * 2^m * |E| * Sum of lengths of patterns) per test

*/

const int SUML = 103;
const int MASK = 1<<10;
const int N = 26;
const int E = 26;

int n;
int m;
int k;
int nodes;
char s[15];
int suf[SUML];
int bmask[SUML];
int go[SUML][E];
int trie[SUML][E];
int memo[N][SUML][MASK];
bool vis[N][SUML][MASK];

void addNode(int u){
	suf[u] = bmask[u] = 0;
	for(int i = 0; i < E; i++) go[u][i] = trie[u][i] = 0;
}

void insert(int npat){
	int pos = 0;
	for(int i = 0; s[i]; i++){
		int nxt = s[i] - 'a';
		if(trie[pos][nxt] == 0){
			addNode(nodes);
			trie[pos][nxt] = nodes++;
		}
		pos = trie[pos][nxt];
	}
	bmask[pos] |= 1<<(npat);
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		bmask[u] |= bmask[suf[u]];
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
				suf[v] = u ? go[suf[u]][i] : 0;
				Q.emplace(v);
			}
		}
	}
}

void buildAutomaton(int npat){
	nodes = 1;
	addNode(0);
	for(int i = 0; i < npat; i++){
		scanf("%s", s);
		insert(i);
	}
	BFS(0);
}

int solve(){
	for(int i = 0; i <= n; i++){
		for(int j = 0; j < nodes; j++){
			for(int p = 0; p < 1<<m; p++){
				memo[i][j][p] = 0;
			}
		}
	}
	queue<int> Q;
	Q.emplace(0);
	Q.emplace(0);
	Q.emplace(0);
	memo[0][0][0] = 1;
	vis[0][0][0] = true;
	while(!Q.empty()){
		int pos = Q.front(); Q.pop();
		int state = Q.front(); Q.pop();
		int mask = Q.front(); Q.pop();
		if(pos < n){
			for(int i = 0; i < E; i++){
				int npos = pos + 1;
				int nstate = go[state][i];
				int nmask = bmask[nstate] | mask;
				memo[npos][nstate][nmask] = add(memo[npos][nstate][nmask], memo[pos][state][mask]);
				if(!vis[npos][nstate][nmask]){
					Q.emplace(npos);
					Q.emplace(nstate);
					Q.emplace(nmask);
					vis[npos][nstate][nmask] = true;
				}
			}
		}
		vis[pos][state][mask] = false;
	}
	int ans = 0;
	for(int mask = 0; mask < 1<<m; mask++){
		if(__builtin_popcount(mask) < k) continue;
		for(int state = 0; state < nodes; state++){
			ans = add(ans, memo[n][state][mask]);
		}
	}
	return ans;
}

int main(){
	while(ri3(n, m, k) == 3 and n + m + k){
		buildAutomaton(m);
		if(k > m){
			puts("0");
			continue;
		}
		printf("%d\n", solve());
	}
	return 0;
}
