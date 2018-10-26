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
		- Nice DP problem.

		- First, let's notice that the optimal solution will be an interval
		  of restaurants and there's actually no need to turn backwards.

		- Now, it only reduces to the following:

		  Ans = max_{i < j}(compute(i,j))

		  where we can get the compute function in amortized O(m) with a Sparse table
		  preprocessing.

		- Now, we need to notice that if we fix the start L of the interval
		  
		  and set it's optimal end as K, then the optimal end for L+1 will

		  be >= K.

		  Thus, we can use Divide and Conquer Optimization for this problem.
		
		  Observation: Just realize that if we denote max(L,R) as the maximum

		  of the elements in an subarray a[L...R], then:

		  max(a,d) + max(b,c) <= max(a,c) + max(b,d) with a <= b <= c <= d

		  This is sufficient to apply Divide and Conquer Optimization for maximum


		- Complexity: O(mnlogn)
*/

const int N = 5000+5;
const int M = 200+5;
const int LOG = 18;

int n,m;
ll a[N];
ll ans;
int bestL, bestR;
int b[N][M];
int ST[M][N][LOG];

void startSparseTable(){
	for(int k=0; k<m; k++){
		for(int i=0; i<n; i++){
			ST[k][i][0] = b[i][k];
		}
		for(int d=1; 1<<d <= n; d++){
			int dis = 1<<(d-1);
			for(int i=0; i+2*dis-1 < n; i++){
				ST[k][i][d] = max(ST[k][i][d-1],ST[k][i+dis][d-1]);
			}
		}
	}
}

int getMax(int k, int x, int y){
	if(x == y) return b[x][k];
	int d = y-x+1;
	int bit = 31 - __builtin_clz(d);
	int dis = 1<<bit;
	return max(ST[k][x][bit],ST[k][y-dis+1][bit]);
}

ll compute(int L, int R){
	ll act = 0LL;
	for(int i=0; i<m; i++){
		act += getMax(i,L,R);
	}
	act -= a[R] - a[L];
	return act;
}

void solve(int L, int R, int optL, int optR){
	if(L > R) return;
	int mi = (L+R)/2;
	ll midAns = 0LL;
	int midBest = optL;
	for(int i=max(mi,optL); i<=optR; i++){
		ll cand = compute(mi,i);
		if(midAns < cand){
			midBest = i;
			midAns = cand; 
		}
	}
	if(ans < midAns){
		ans = midAns;
		bestL = mi;
		bestR = midBest;
	}
	if(L < R){
		solve(L,mi-1,optL,midBest);
		solve(mi+1,R,midBest,optR);
	}
}

int main(){
	ri2(n,m);
	for(int i=1; i<n; i++) rll(a[i]);
	for(int i=1; i<n; i++) a[i] += a[i-1];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			ri(b[i][j]);
		}
	}
	startSparseTable();
	ans = 0LL;
	solve(0,n-1,0,n-1);
	printf("%lld\n",ans);
	return 0;
}
