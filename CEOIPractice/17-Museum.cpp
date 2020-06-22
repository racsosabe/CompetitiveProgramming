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

	- Classic DP on Trees problem

	- Basically, we can define our recursion DP(u, used, returned) as the minimum

	  distance required to visit "used" rooms in the subtree of node "u" given that

	  we will return to "u" after that if "returned = 0"  and we won't return

	  if "returned = 1". The recursion step is easy to see.

	- Solving directly with that recursion would take a long time for fixing the

	  value "used" for the children of "u", so we will use a Knapsack style DP

	  over the subtree but only allowing "used" values that are less than or equal

	  the size of the subtree of "u".

	- By using the previous technique, we will achieve a complexity of O(nk)

	- Complexity Proof: https://codeforces.com/blog/entry/63257
*/

const int N = 10000+5;
const int inf = 1<<30;

int n;
int k;
int r;
vi G[N];
vi W[N];
int temp1[N];
int temp2[N];
int subtree[N];
int memo[N][N][2];

void DP(int u, int p = 0){
	subtree[u] = 1;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		int w = W[u][i];
		if(v == p) continue;
		DP(v, u);
		fill(temp1, temp1 + k + 1, inf);
		fill(temp2, temp2 + k + 1, inf);
		temp1[0] = temp2[0] = temp1[1] = temp2[1] = 0;
		for(int s1 = 0; s1 <= min(subtree[u], k); s1++){
			for(int s2 = 0; s2 <= subtree[v] and s1 + s2 <= k; s2++){
				temp1[s1 + s2] = min(temp1[s1 + s2], memo[u][s1][0] + 2 * w * (s2 > 0) + memo[v][s2][0]);
				temp2[s1 + s2] = min(temp2[s1 + s2], memo[u][s1][0] + w * (s2 > 0) + memo[v][s2][1]);
				temp2[s1 + s2] = min(temp2[s1 + s2], memo[u][s1][1] + 2 * w * (s2 > 0) + memo[v][s2][0]);
			}
		}
		subtree[u] += subtree[v];
		for(int i = 0; i <= min(k, subtree[u]); i++){
			memo[u][i][0] = temp1[i];
			memo[u][i][1] = temp2[i];
		}
	}
}

int main(){
	ri3(n,k,r);
	for(int i=1; i<n; i++){
		int u, v, w;
		ri3(u,v,w);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		W[u].emplace_back(w);
		W[v].emplace_back(w);
	}
	DP(r);
	printf("%d\n",min(memo[r][k][0], memo[r][k][1]));
	return 0;
}
