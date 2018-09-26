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
		- Good DP & Matrix Exponentiation problem.

		- First, intuitively choose some 2k such that

		  We can form a matrix M of 2k x 2k that we can

		  use it to get M^m to find the answer.

		- We can say that M[i][j] is the minimum cost to

		  get from a balance of i to a balance of j in n

		  positions.

		- Thus, our answer will be (M^m)[0][0].

		- Now, to compute all the values of the matrix, we'll

		  see that if we make a DP for each possible initial

		  balance b, we can compute M[b][i] for each i=0,...,2k

		  in O(n^2), by using this simple recursion:

		  memo[i][j]: minimum cost to get balance j with the first

		  i positions.

		  memo[i][j] = min(memo[i-1][j-1]+a[i],memo[i-1][j+1]+b[i])

		  Since we can achieve a balance of j by adding a open bracket

		  to a balance of (j-1) or adding a close bracket to a (j+1) one.

		- Set memo[0][b] = 0 and compute it again for each b.

		- We can choose 2k >= 2n to be safe (Min Correct Balance isn't less than 2n).

		- Our multiply function will get:

		  C[i][j] = min(A[i][l]+B[l][j]) for all l=0,..,2k

		  And our Identity will have infinite in every position not in

		  the diagonal of the matrix.

		- Complexity: O(n^3 logm)
*/

const int N = 20+5;
const int E = 40+5;
const int inf = 2100000000;

int n, k, m;
int a[N];
int b[N];
int r[E][E];
int M[E][E];

void compute_transition(vector<vi> &memo, int x){
	for(int i=0; i<=n; i++){
		for(int j=0; j<m; j++) memo[i][j] = inf;
	}
	memo[0][x] = 0;
	for(int i=1; i<=n; i++){
		for(int j=0; j<m; j++){
			if(j) memo[i][j] = min(memo[i][j],memo[i-1][j-1]+a[i]);
			if(j+1 < m) memo[i][j] = min(memo[i][j],memo[i-1][j+1]+b[i]);
		}
	}
}

void preprocess(){
	vector<vi> memo;
	memo.resize(n+1);
	for(int i=0; i<=n; i++) memo[i].resize(m);
	for(int ibalance = 0; ibalance < m; ibalance++){
		compute_transition(memo,ibalance);
		for(int i=0; i<m; i++){
			M[ibalance][i] = memo[n][i];
		}
	}
}

void multiply(int a[][E], int b[][E]){
	int c[E][E];
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			c[i][j] = inf;
			for(int k=0; k<m; k++){
				ll carry = 1LL*a[i][k] + 1LL*b[k][j];
				if(c[i][j] > carry) c[i][j] = a[i][k]+b[k][j];
			}
		}
	}
	for(int i=0; i<m; i++)
		for(int j=0; j<m; j++) a[i][j] = c[i][j];
	
}

int fast_expo(){
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			r[i][j] = i==j?0:inf;
		}
	}
	int A[E][E];
	for(int i=0; i<m; i++)
		for(int j=0; j<m; j++) A[i][j] = M[i][j];
	while(k){
		if(k&1){
			multiply(r,A);
		}
		k >>= 1;
		multiply(A,A);
	}
	return r[0][0];
}

int main(){
	ri2(n,k);
	m = 2*n+1;
	for(int i=1; i<=n; i++){
		ri(a[i]);
	}
	for(int i=1; i<=n; i++){
		ri(b[i]);
	}
	preprocess();
	printf("%d\n",fast_expo());
	return 0;
}
