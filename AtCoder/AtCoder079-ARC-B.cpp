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
		- Interesting math problem. Prepare for the solution :D

		- First of all, notice that there is always a possible answer with n = 50
		  since we can make some values equal to 0 if they don't match, but that
		  
		  doesn't really matter in the end.

		- Then, analize the case when k = r < n: 

		  For this, we will need that exactly k values are taken, thus

		  a valid solution for this is:

		  a[i] = i if i < n - r
		  a[i] = n otherwise

		  Let's denote cur[i] = current value of position i, so initially cur[i] = a[i] for all i.

		  The simulation will take the value rightmost maximum value, thus

		  In the p-th step, the rightmost maximum element is the (n-p)-th one

		  Why? Since we are taking the rightmost maximum value, then the

		  (p-1) last elements won't be maximum anymore (since their values are too small)
		  
		  and all of the first (n-p) elements grow at the same rate before choosing a maximum.

		  Since a[n-p] is initially n for each p = 1,...,r and each of them
		  
		  grow at the same rate, then cur[n-p] is chosen in the p-th step for p = 1,...,r

		  Now, let's check if the (r+1)-th step will choose any of the values:

		  We know that the only candidates remaining are 0 <= i < n-r, but

		  they are initially a strictly increasing sequence and they grow at the same rate.

		  Thus, cur[n-(r+1)] = cur[n-r-1] is the maximum current value.

		  However, it holds that:

		  cur[n-r-1] = a[n-r-1] + r

		  But, n-r-1 < n-r, so a[n-r-1] = n-r-1

		  cur[n-r-1] = n - r - 1 + r = n - 1

		  So cur[n-r-1] won't be chosen in the (r+1)-th step and the simulation stops there.

		- Finally, notice that if all the values are >= n, then after n steps 

		  all of them will be reduced by 1, so we can just take the former structure

		  and add 1 to all initial elements when we want to increase the number of steps by n.

		  Thus, we add (k / n) to all values and take r = k % n.

		- Complexity: O(n) where n = 50
*/

const int N = 50+5;

ll k;
int n = 50;
ll a[N];

int main(){
	rll(k);
	int r = k % n;
	for(int i=0; i<n; i++){
		a[i] += i;
	}
	for(int i=0; i<r; i++){
		a[n-1-i] = n;
	}
	for(int i=0; i<n; i++){
		a[i] += (k / n);
	}
	printf("%d\n",n);
	for(int i=0; i<n; i++){
		printf("%lld%c",a[i]," \n"[i+1==n]);
	}
	return 0;
}
