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

const int N = 50000 + 5;
const int K = 2000 + 5;
const ll inf = 1e18;
const int E = 26;

int n;
int k;
int h[N];
char s[505];
int nodes = 1;
ll memo[K][N];
map<int, int> trie[N];
int subtree[N];

void insert(){
	int pos = 0;
	for(int i = 0; s[i]; i++){
		int nxt = s[i] - 'a';
		if(!trie[pos].count(nxt)){
			trie[pos][nxt] = nodes++;
		}
		pos = trie[pos][nxt];
		h[pos] = i + 1;
	}
	subtree[pos] += 1;
}

void DP(int u){
	vector<ll> carry(k + 1);
	for(int i = 0; i <= subtree[u]; i++){
		memo[i][u] = 1LL * h[u] * i * (i - 1) / 2LL;
	}
	for(auto x : trie[u]){
		int v = x.second;
		DP(v);
		carry.assign(k + 1, 0LL);
		for(int i = 0; i <= min(subtree[u], k); i++){
			for(int j = 0; j <= subtree[v] and i + j <= k; j++){
				carry[i + j] = max(carry[i + j], memo[i][u] + 1LL * i * j * h[u] + memo[j][v]);
			}
		}
		subtree[u] += subtree[v];
		for(int i = 0; i <= min(subtree[u], k); i++){
			memo[i][u] = max(memo[i][u], carry[i]);
		}
	}
}

int main(){
	ri2(n, k);
	for(int i=0; i<n; i++){
		scanf("%s", s);
		insert();
	}
	DP(0);
	printf("%lld\n", memo[k][0]);
	return 0;
}
