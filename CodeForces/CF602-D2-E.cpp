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
		- Nice DP & Expected Value problem.

		- First of all, notice that out answer will be

		  Ans = 1.0 + sum E(X) for each X < sum(x_i)

		  Since we will add each way such that the final

		  score is less than the score given. All of this is

		  possible because of linearity of Expectation.

		- We can compute the expected number of people with

		  final score X with a DP:

		  memo[i][X]: Expected number of people with score X

		  in the first i competitions.

		  It's obvious that:

		  memo[i][X] = sum(memo[i-1][X-k]*p(k)) for each k <= X

		  Where p(k) is the probability of getting rank k in the

		  last round.

		  Also that:

		  memo[0][0] = m-1, since m-1 people don't have a fixed rank.

		- Since all permutations are equally probable, we see that

		  for k != x_(i-1) p(k) = 1/(m-1), because we can choose

		  1 out of m-1 people to get this rank and when k = x_(i-1) is 0.

		- To improve the naive TLE solution, we can propagate from round
		  i to i+1 by using preffix sums, taking care that we didn't
		  use x_i.

		- Complexity: O(n^2 m)
*/

const int MAX = 1000000+5;
const int N = 100+5;

int n, m;
int v[N];
long double memo[2][MAX];

int main(){
	ri2(n,m);
	int S = 0;
	for(int i=1; i<=n; i++){
		ri(v[i]);
		S += v[i];
	}
	long double ans = 0.0;
	if(m > 1){
		memo[0][0] = m-1;
		for(int i=0; i<n; i++){
			int next = (i+1)&1;
			int act = i&1;
			for(int j=1; j<=n*m; j++){
				memo[act][j] += memo[act][j-1];
			}
			for(int j=0; j<=n*m; j++){
				memo[next][j] = 0.0;
			}
			int next_chosen = v[i+1];
			for(int j=0; j<=i*m; j++){
				memo[next][j+1] += memo[act][j]/(m-1);
				memo[next][j+m+1] -= memo[act][j]/(m-1);
				memo[next][j+next_chosen] -= memo[act][j]/(m-1);
				memo[next][j+next_chosen+1] += memo[act][j]/(m-1);
			}
		}
		for(int j=1; j<=n*m; j++){
			memo[n&1][j] += memo[n&1][j-1];
		}
		for(int j=0; j<S; j++){
			ans += memo[n&1][j];
		}
	}
	ans += 1.0;
	printf("%.16Lf\n",ans);
	return 0;
}
