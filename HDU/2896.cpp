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

	- Strict ML Aho-Corasick problem.

	- First, notice that you can use the trie array as a go array after inserting

	  all the patterns.

	- Also you must notice that if you want to mark a node as visited you can

	  just assign a timestamp (let it be the site ID) to optimize a little the

	  execution time.

	- Don't use more memory that you would need, so an array of size [4,6] should

	  be enough for storing the number of viruses (since the maximum is 3 per
	  
	  site). After getting the viruses IDs you will sort in O(1).

	  Also, the maximum ASCII value of a visible character is 126.

	- Complexity: O(n * |E| + m), where n is the sum

	  of lengths of the patterns and m is the sum of lengths of queries.
*/

const int SUML = 500 * 200 + 3;
const int N = 500+5;
const int E = 128;

int n;
int m;
int nodes;
int ans[6];
int pat[SUML];
int vis[SUML];
int trie[E][SUML];
int suf[SUML];

void insert(int npat){
	int pos = 0;
	char c = getchar();
	while(c != '\n'){
		int nxt = c;
		if(!trie[nxt][pos]){
			trie[nxt][pos] = nodes++;
		}
		pos = trie[nxt][pos];
		c = getchar();
	}
	pat[pos] = npat;
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int i = 0; i < E; i++){
			if(trie[i][u]){
				int v = trie[i][u];
			suf[v] = u ? trie[i][suf[u]] : 0;
				Q.emplace(v);
			}
			else{
				trie[i][u] = u ? trie[i][suf[u]] : 0;
			}
		}
	}
}

void buildAutomaton(int npat){
	nodes = 1;
	for(int i = 1; i <= npat; i++){
		insert(i);
	}
	BFS(0);
}

void mark(int u, int id){
	while(u > 0 and vis[u] < id){
		if(pat[u]){
			ans[++ans[0]] = pat[u];
		}
		vis[u] = id;
		u = suf[u];
	}
}

bool query(int id){
	memset(ans, 0, sizeof ans);
	char c = getchar();
	int state = 0;
	while(c != '\n'){
		state = trie[c][state];
		mark(state, id);
		c = getchar();
	}
	if(ans[0]){
		sort(ans + 1, ans + ans[0] + 1);
		printf("web %d:", id);
		for(int i = 1; i <= ans[0]; i++){
			printf(" %d", ans[i]);
		}
		putchar('\n');
		return true;
	}
	else return false;
}

int main(){
	ri(n);
	getchar();
	buildAutomaton(n);
	ri(m);
	getchar();
	int sites = 0;
	for(int j = 1; j <= m; j++){
		sites += query(j);
	}
	printf("total: %d\n", sites);
	return 0;
}
