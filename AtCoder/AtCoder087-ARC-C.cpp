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
		- Hard to think game theory problem.

		- First of all, if we model the strings in a trie, we initially have

		  a complete binary tree full of empty nodes and of height L.

		- When we add a string to the trie, we will mark some of their nodes

		  as visited, so none of those nodes can be the end of any following string.

		  Also, since this string itself can't be the prefix of another one

		  we also mark the whole subtree of the end node as visited.

		- Observation: The nodes that are not visited form a disjoint set

		  of complete binary trees full of empty nodes

		- We can solve those states independently, so we need to compute their

		  Grundy numbers considering their height (since it's the best value
		  
		  choice for it) and have the XOR sum of them.

		- The computation of Grundy Numbers is explained in the Official Editorial.
		  
		  If the XOR sum is 0, Bob wins; else, Alice wins.

		- Complexity: O(|S|).


*/

const int N = 100000+5;
const int E = 3;

ll L;
int n;
char s[N];
bool leaf[N];
int nodos = 1;
int trie[N][E];

void insert(){
	int pos = 0;
	for(int i=0; i<strlen(s); i++){
		int nxt = s[i] - '0';
		if(trie[pos][nxt] == 0){
			trie[pos][nxt] = nodos++;
		}
		pos = trie[pos][nxt];
	}
	leaf[pos] = true;
}

ll getGrundy(int u, int depth){
	if(leaf[u]) return 0LL;
	ll ans = 0;
	for(int i=0; i<2; i++){
		if(trie[u][i]){
			ans ^= getGrundy(trie[u][i],depth+1);
		}
		else{
			ll h = L - depth;
			ll G = (-h) & h;
			ans ^= G;
		}
	}
	return ans;
}

int main(){
	ri(n);
	rll(L);
	for(int i=0; i<n; i++){
		scanf("%s",s);
		insert();
	}
	ll grundy = getGrundy(0,0);
	puts(grundy?"Alice": "Bob");
	return 0;
}
