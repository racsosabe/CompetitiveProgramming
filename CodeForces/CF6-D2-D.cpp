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

	- Simulation DP problem

	- Since the order of the fireballs is not important, we'll assume wlog that

	  they are in increasing order of archer ID.

	- Thus, we can solve the problem by analyzing how many times we'll shoot 

	  the fireballs to the pos-th archer, but since it can affect the (pos-1)-th

	  one we must know its health points to possibly reduce the number of shots

	  that are directly to it.

	- We can use the recursion DP(pos,lasth,myh) that gets the minimum number

	  of fireballs to kill all the archers from (pos-1) to (n-1)-th (0-indexed)

	  given that we already killed all the ones from 0 to (pos-2).

	- To avoid using negative values, we can just increase 1 HP to each archer

	  and with this, we can assume that HP = 0 is equivalent to death.

	- Complexity: O(MaxHP^3 * n)

*/

const int N = 15;
const int MAX = 20;
const int inf = 1<<29;

int n;
int a, b;
int v[N];
bool vis[N][MAX][MAX];
int memo[N][MAX][MAX];
int choice[N][MAX][MAX];

int DP(int pos, int lasth, int myh){
	if(pos == n-1){
		return lasth == 0 and myh == 0? 0 : inf;
	}
	if(vis[pos][lasth][myh]) return memo[pos][lasth][myh];
	int ans = inf;
	int minimum = (lasth + b - 1) / b;
	for(int i=minimum; i <= 16; i++){
		int cand = i + DP(pos+1, max(0, myh - i * a), max(0, v[pos+1] - i * b));
		if(cand < ans){
			ans = cand;
			choice[pos][lasth][myh] = i;
		}
	}
	vis[pos][lasth][myh] = true;
	return memo[pos][lasth][myh] = ans;
}

int main(){
	ri3(n,a,b);
	for(int i=0; i<n; i++){
		ri(v[i]);
		v[i] += 1;
	}
	int ans = DP(1,v[0],v[1]);
	printf("%d\n",ans);
	vi arr;
	int h1 = v[0], h2 = v[1];
	for(int i=1; i+1<n; i++){
		int times = choice[i][h1][h2];
		for(int j=0; j<times; j++){
			arr.emplace_back(i + 1);
		}
		h1 = max(0, h2 - times * a);
		h2 = max(0, v[i+1] - times * b);
	}
	for(int i=0; i<ans; i++){
		printf("%d%c",arr[i]," \n"[i + 1 == ans]);
	}
	return 0;
}
