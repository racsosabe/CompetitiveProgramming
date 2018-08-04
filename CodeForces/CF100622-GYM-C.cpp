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
		- Easy greedy problem.

		- Just notice that we can actually distribute the painted cells as intervals
		  Because of constraints, we can brute force it for each row.

		  Let's set a row X from a center (x,y) with radius r, then the interval would be
		  [max(y-d,0),min(y+d,h-1)] where d is the greatest number such that
		  (X-x)^2 + d^2 <= r^2 (we can binary search it)
		
		- Then, for each row, merge intervals by using a position pointer
		  that will store the current position (so we don't double count
		  
		  already painted cells) and add all painted ones to a counter act
		- The answer is h*w - \sum\limits_{row=0}^{w-1}act_{i}.

		- Complexity: O(wnlogA). where w and n are according to the statement
		  and A is the maximum radius value.

*/

const int N = 20000+5;

int n;
int h,w;
vii rows[N];

int getRoot(int c, int b){
	int lo = 0, hi = 40000;
	while(lo < hi){
		int mi = lo + (hi-lo+1)/2;
		if(b*b + mi*mi <= c*c) lo = mi;
		else hi = mi-1;
	}
	return lo;
}

int main(){
	freopen("circles.in","r",stdin);
	ri3(w,h,n);
	int x,y,r;
	int L,R;
	for(int i=0; i<n; i++){
		ri3(x,y,r);
		for(int row = max(0,x-r); row<=min(w-1,x+r); row++){
			int d = getRoot(r,abs(x-row));
			L = max(0,y-d);
			R = min(h-1,y+d);
			rows[row].pb(mp(L,R));
		}
	}
	int ans = 0;
	for(int i=0; i<w; i++){
		sort(all(rows[i]));
		int p = 0;
		int pos = 0;
		int act = 0;
		for(int j=0; j<rows[i].size(); j++){
			if(p < rows[i][j].first){
				p = rows[i][j].second+1;
				act += rows[i][j].second - rows[i][j].first+1;
			}
			else{
				act += max(0,rows[i][j].second-p+1);
				p = max(p,rows[i][j].second+1);
			}
		}
		ans += h-act;
	}
	freopen("circles.out","w",stdout);
	printf("%d\n",ans);
	return 0;
}
