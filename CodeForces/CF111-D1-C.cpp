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

	- DP Broken Profile problem

	- Let's consider that we want to minimize the number of occupied cells instead
	 
	  of maximize the unoccupied ones.

	- If we fix a cell (x, y) as a occupied cell, then all neighboring spiders

	  can go to this cell, thus we can say that those cells are "covered".

	- Since n * m <= 40 then min(n, m) <= 6. Also, since the "covering" doesn't

	  depend on the orientation, we can just swap n and m if n is greater than m

	- We can use a DP Broken Profile style to carry two masks: 1 for the already
	 
	  covered cells in the former column and another for the ones considered 

	  in the current column.

	- Make the correct transitions considering that the former cells MUST be 

	  completely covered (cell (x, y - 1) must be covered after making the transition
	  
	  with cell (x, y), since it's the last possibility for that to happen).


	- Complexity: O(n m 4^min(n, m))

*/

const int N = 40+5;
const int MASK = 1<<6;
const int inf = 50;

int n, m;
bool vis[N][N][MASK][MASK];
int memo[N][N][MASK][MASK];

int DP(int x, int y, int mask, int covered){
	if(y == m){
		return covered + 1 == (1<<n)? 0 : inf;
	}
	if(vis[x][y][mask][covered]) return memo[x][y][mask][covered];
	int ans = inf;
	int last = (mask >> x) & 1;
	int nx = x + 1 < n ? x + 1 : 0;
	int ny = x + 1 < n ? y : y + 1;
	if((covered >> x) & 1){
		int new_covered = covered & (~(1<<x));
		new_covered |= last << x;
		if(x > 0 and mask & (1<<(x-1))) new_covered |= 1<<x;
		ans = min(ans, DP(nx, ny, mask & (~(1<<x)), new_covered));
	}
	int new_covered = covered & (~(1<<x));
	new_covered |= 1 << x;
	if(x > 0) new_covered |= 1<<(x-1);
	ans = min(ans, 1 + DP(nx, ny, (mask & (~(1<<x))) | (1<<x), new_covered));
	vis[x][y][mask][covered] = true;
	return memo[x][y][mask][covered] = ans;
}

int main(){
	ri2(n, m);
	if(n > m) swap(n, m);
	assert(n <= 6);
	printf("%d\n",n * m - DP(0, 0, 0, (1<<n) - 1));
	return 0;
}
