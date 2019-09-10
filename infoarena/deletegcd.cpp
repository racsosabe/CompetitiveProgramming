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
		- Interesting Sieve + Two pointers problem

		- One must notice that the only condition needed to answer 1 is that
		  it must exist a prime p such that it divides at least R-L numbers
		  in the interval.

		- Now, let's see that if we fix L and get the maximum R such that

		  (L,R) is a valid interval (answer is 1), then we can use two pointers

		  to compute the maximum R' for (L+1), since (L+1,R) must be valid, too
		  (just 2 cases: 1. if the one of (L,R) that isn't divisible by the prime p
		  
		  is L, then (L+1,R) will have all it's values divisible by p. 2. 
		  
		  if the index of the value that isn't divisible by p is in the interval (L+1,R)
		  
		  then the interval (L+1,R) will have R-L-1 values divisible by p, thus
		  
		  it's valid. The cases when all the interval values are divisible are
		  
		  trivial).

		- If we precompute all the prime factors of each number with a sieve
		 
		  we can solve the problem efficiently and answer each query in O(1).

		- Complexity: O(MAX log(MAX) + q)

*/

const int N = 1000000+5;

int n;
int q;
int a[N];
int Q[N];
int pf[N];
int maxR[N];
int frec[N];
int sqfree[N];

void init(){
	for(int i=1; i<N; i++) pf[i] = i;
	for(int i=2; i*i<=N; i++){
		if(pf[i] == i){
			for(int j = i*i; j<N; j+=i){
				pf[j] = i;
			}
		}
	}
	for(int i=1; i<N; i++){
		int sqf = 1;
		int x = i;
		while(x != 1){
			int f = pf[x];
			while(x % f == 0) x /= f;
			sqf *= f;
		}
		sqfree[i] = sqf;
	}
}

void preprocess(){
	int R = 1;
	Q[0] = 1e6;
	for(int L=1; L<=n; L++){
		while(R <= n){
			for(int x = a[R]; x != 1; x /= pf[x]){
				int f = pf[x];
				Q[frec[f]] -= 1;
				Q[++frec[f]] += 1;
			}
			if(!(Q[R-L]|Q[R-L+1])){
				for(int x = a[R]; x != 1; x /= pf[x]){
					int f = pf[x];
					Q[frec[f]] -= 1;
					Q[--frec[f]] += 1;
				}
				break;
			}
			R += 1;
		}
		maxR[L] = R-1;
		for(int x = a[L]; x != 1; x /= pf[x]){
			int f = pf[x];
			Q[frec[f]] -= 1;
			Q[--frec[f]] += 1;
		}
	}
}

int main(){
	init();
	freopen("deletegcd.in","r",stdin);
	freopen("deletegcd.out","w",stdout);
	ri2(n,q);
	int x;
	for(int i=1; i<=n; i++){
		ri(x);
		a[i] = sqfree[x];
	}
	preprocess();
	int l, r;
	while(q--){
		ri2(l,r);
		putchar(r <= maxR[l] ? '1': '0');
	}
	puts("");
	return 0;
}
