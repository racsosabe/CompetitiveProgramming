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
		- Simple math problem.

		- First, notice that we only need the following

		  sum:

		  S = sum for d in range(2,n+1): d*(floor(n/d) - 1)

		- So, we only need to cleverly compute

		  sum for d in range(2,n+1) d*floor(n/d)

		  since the -d is easily computable.

		- Now, ¿What if we fix x = floor(n/d)? Then we will see

		  that there will be O(sqrt(n)) different values of x

		  and that if we can compute the ranges fast enough

		  we already solved the problem.

		- Finally, use two pointers, l = 1 and r = 2 initially so

		  that you add floor(n/r)*(range of d's for floor(n/r)).

		  If we set maxi as our upper bound (which is floor(n/floor(n/r)) )

		  then we would update l = maxi and then r = maxi+1.

		  Do this until r > n. In the end, take off the -d for each d, which

		  is sum(n) - 1.

		- Complexity: O(Tsqrt(n)), where T is the number of test cases.

*/

int n;

ll sum(ll x){
	return x*(x+1)/2LL;
}

int main(){
	int t = 1;
	while(ri(n)==1 and n){
		int l = 1;
		int r = 2;
		ll ans = 0LL;
		while(r <= n){
			int x = n/r;
			int maxi = n/x;
			ans += 1LL*(sum(maxi) - sum(l))*x;
			l = maxi;
			r = maxi+1;
		}
		ans -= sum(n) - 1;
		printf("Case %d: %lld\n",t++,ans);
	}
	return 0;
}
