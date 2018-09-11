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
		- DP + Inclusion-Exclusion Principle

		- First, let's notice that we need to order the

		  pairs by (row,col).

		- Once we have them ordered, we need to find the

		  number of paths such that they avoid all points.

		- Thus, we can set the memo[pos] table as the number
		  
		  of paths from (1,1) to (x_pos,y_pos) such that they

		  avoid every previous point. We can add (h,w) to the

		  set of points and thus the answer will be memo[n]

		- Now, we see that it's better to take off the paths

		  that do cross any of the previous points from the total.

		  Therefore, we have:

		  memo[pos] = C(x_pos+y_pos-2,x_pos-1) - X(pos)

		- Now, we see that if we take off each previous point that
		 
		  can be crossed before (x_pos,y_pos) we won't be double

		  counting any path and even we'll be counting all of them once.

		- Finally, we get:

		  X(pos) = \sum\limits_{i=0}^{pos-1}C(d(P_pos,P_i),dx(P_pos,P_i))*memo[i]

		- Complexity: O((H+W) + n^2)
*/

const int M = 200000+5;
const int N = 2000+5;

int h,w,n;
vii v;
ll f[M];
ll fi[M];
ll paths[N];

void init(){
	f[0] = 1;
	for(int i=1; i<M; i++){
		f[i] = mul(i,f[i-1]);
	}
	fi[M-1] = pow_mod(f[M-1],MOD-2);
	for(int i=M-2; i>=0; i--){
		fi[i] = mul(i+1,fi[i+1]);
	}
}

ll C(int n,int k){
	ll ans = f[n];
	ans = mul(ans,fi[n-k]);
	ans = mul(ans,fi[k]);
	return ans;
}

int main(){
	init();
	ri3(h,w,n);
	int x,y;
	for(int i=0; i<n; i++){
		ri2(x,y);
		v.pb(mp(x,y));
	}
	v.pb(mp(h,w));
	sort(all(v));
	for(int i=0; i<=n; i++){
		paths[i] = C(v[i].first+v[i].second-2,v[i].first-1);
		for(int j=0; j<i; j++){
			if(v[j].first <= v[i].first and v[j].second <= v[i].second){
				int dx = v[i].first - v[j].first;
				int dy = v[i].second - v[j].second;
				paths[i] = add(paths[i],mul(MOD-1,mul(paths[j],C(dx+dy,dx))));
			}
		}
	}
	ll ans = paths[v.size()-1];
	printf("%lld\n",ans);
	return 0;
}
