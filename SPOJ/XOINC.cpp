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

ll add(ll a, ll b, ll m = MOD){ return (a%m + b%m+2*m)%m;}

ll mul(ll a, ll b, ll m = MOD){ return ((a%m+m)*(b%m+m))%m;}

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
		- Tricky DP Problem

		- Let's denote our DP function as 

		  DP(pos,allow): Best sum that current player can get

		  while using at most "allow" coins from "pos".

		- Notation: suffix[i]: Sum of elements from i to n-1.

		- So, first of all, DP(pos,allow) = max_{1<=i<=allow}(pos,i)

		  But we can't simply do that, so we are going to take care of

		  i = allow case, which is:

		  Sum of player when using allow coins: 

		  S = suffix[pos] - DP(pos+allow,2*allow)

		  That is because we are considering to take everything and deleting
		  
		  the other player's part (which is DP(pos+allow,2*allow)).

		- Now, we can say that:

		  DP(pos,allow) = max(DP(pos,allow-1),suffix[pos]-DP(pos+allow,2*allow))

		  Also, when pos < 0 the answer is 0, when allow = 1 the form

		  is directly take the only element available

		  Finally, to avoid incoherent cases, when allow > n-pos we do

		  DP(pos,allow) = DP(pos,n-pos)

		  Call DP(0,2) to get the answer.

		- Complexity: O(n^2)

*/

const int N = 2000+5;
const int M = 1024+5;

int n;
int v[N];
int suffix[N];
int memo[N][M];
bool vis[N][M];

int DP(int pos, int allow){ // Best sum at pos and at most allow coins
	if(pos == n) return 0;
	if(allow == 1){
		return memo[pos][allow] = suffix[pos] - DP(pos+1,2);
	}
	if(allow > n-pos) return DP(pos,n-pos);
	if(vis[pos][allow]) return memo[pos][allow];
	vis[pos][allow] = true;
	return memo[pos][allow] = max(DP(pos,allow-1),suffix[pos]-DP(pos+allow,2*allow));
}

int main(){
	ri(n);
	int S = 0;
	for(int i=0; i<n; i++){
		ri(v[i]);
	}
	for(int i=n-1; i>=0; i--){
		suffix[i] = suffix[i+1]+v[i];
	}
	int ans = DP(0,2);
	printf("%d\n",ans);
	return 0;
}
