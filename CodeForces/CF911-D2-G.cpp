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
		- Interesting Data Structures problem.

		- Let's denote a function f(x) = y that implies that the value of x
		  will change to y as stated in the problem.

		  It's easy to see that f(x) = x initially.

		- Now, we need to consider the moment of the change to do a correct transition
		  That means that if we make two changes x -> y and y -> z after it,
		  then we are actually taking a function G such that 

		  G = f_{2}(f_{1}(x)), which is the composition of functions.

		  With this, we know that composition is associative. Therefore, we can
		  use a Segment Tree.

		- We'll store the composition of all transformations in the root node of it
		  So, using "preffix sums", when we add the t-th transformation to interval [L,R]
		  we only add {t,x,y} to ac[l] and {t,x,x} to ac[r+1].

		  The first one to denote the change and the second one to restore it.
		- Finally, for each position get st[1][v[i]] as final value.

*/

const int N = 200000+5;
const int M = 100+5;

int n, q;
int v[N];
queue<iii> ac[N];
int st[4*N][M];

void merge(int target, int a, int b){
	// Composition for the domain of functions
	for(int i=1; i<=100; i++){
		st[target][i] = st[b][st[a][i]];
	}
}

void build(int pos = 1, int l=0, int r=q-1){
	// Initializing functions to identity
	if(l == r){
		for(int j=1; j<=100; j++){
			st[pos][j] = j;
		}
		return;
	}
	int mi = (l+r)/2;
	build(2*pos,l,mi);
	build(2*pos+1,mi+1,r);
	merge(pos,2*pos,2*pos+1);
}

void update(int t, int x, int y, int pos = 1, int l=0, int r=q-1){
	if(l == r){
		st[pos][x] = y;
		return;
	}
	int mi = (l+r)/2;
	if(l <= t and t <= mi) update(t,x,y,2*pos,l,mi);
	else update(t,x,y,2*pos+1,mi+1,r);
	merge(pos,2*pos,2*pos+1);
}

int main(){
	int l,r,x,y;
	ri(n);
	for(int i=0; i<n; i++){
		ri(v[i]);
	}
	ri(q);
	for(int t=0; t<q; t++){
		ri2(l,r);
		ri2(x,y);
		l--; r--;
		ac[l].push(mp(t,mp(x,y)));
		ac[r+1].push(mp(t,mp(x,x)));
	}
	build();
	for(int i=0; i<n; i++){
		while(!ac[i].empty()){
			iii act = ac[i].front(); ac[i].pop();
			update(act.first,act.second.first,act.second.second);
		}
		printf("%d ",st[1][v[i]]);
	}
	return 0;
}
