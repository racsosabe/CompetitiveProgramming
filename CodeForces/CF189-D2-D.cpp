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
		- Interesting DP & Shortest Paths problem. Floyd Warshall-variation.

		- Let's denote a simple function ans(k,i,j) that will give us the

		  minimum distances from i to j using AT MOST k changes. Also let's

		  denote another function d(c,i,j) that will give us the minimum

		  distance from i to j using car c only.

		  Thus, is easy to see that:

		  ans(0,i,j) = min(d(c,i,j)) for each 0 < d < m.

		  Also, we can compute d with Floyd-Warshall algo for each car.

		- Now, let's assume that we have already computed ans(k-1,...), so
		  
		  ans(k,i,j) = min(ans(k-1,i,l) + f(l,v)) for each 0 < l < n

		  Where f(l,v) is some function.

		  Just looking at the function, we see that in the first part we

		  have made at most k-1 changes, so in the transiton with f(l,v) 
		  we are allowed to do at most 1 change.

		  Let's assume that the optimal ending car for ans(k-1,i,l) is C

		  so, f(l,v) must consider both ending with C or changing to other 

		  car and go to v: this is exactly what ans(0,l,v) stores.

		  Finally

		  ans(k,i,j) = min(ans(k-1,i,l)+ans(0,l,v)) for each 0 < l < n

		  which can also be computed with a Floyd-Warshall way.

		- Now, let's notice also that all distances are non-negative, so 
		  any possible cycle will have length >= 0, which means that there

		  is no way that our optimal path has a cycle, no matter how many

		  changes are done, so since at most we will have n-1 cars (for each

		  edge), our maximum k is n-1.

		- Complexity: O((m+n)n^3)

*/

const int N = 60+5;
const int K = 1000+5;

int n,m,r;
ll d[N][N][N];
ll ans[N][N][N];

void floydWarshall(int id){
	for(int k=0; k<n; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(d[id][i][j] > d[id][i][k] + d[id][k][j]){
					d[id][i][j] = d[id][i][k]+d[id][k][j];
				}
			}
		}
	}
}

void solve(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			ans[0][i][j] = -1LL;
			for(int c=0; c<m; c++){
				if(ans[0][i][j] > d[c][i][j] or ans[0][i][j] == -1LL){
					ans[0][i][j] = d[c][i][j];
				}
			}
		}
	}
	for(int ch=1; ch<n; ch++){
		for(int u=0; u<n; u++){
			for(int v=0; v<n; v++){
				if(u==v) continue;
				ans[ch][u][v] = -1LL;
			}
		}
		for(int l=0; l<n; l++){
			for(int u=0; u<n; u++){
				for(int v=0; v<n; v++){
					if(ans[ch][u][v] > ans[ch-1][u][l] + ans[0][l][v] or ans[ch][u][v]==-1){
						ans[ch][u][v] = ans[ch-1][u][l] + ans[0][l][v];
					}
				}
			}
		}
	}
}

int main(){
	ri3(n,m,r);
	for(int k=0; k<m; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				rll(d[k][i][j]);
			}
		}
	}
	for(int i=0; i<m; i++){
		floydWarshall(i);
	}
	solve();
	int u,v,k;
	while(r--){
		ri3(u,v,k);
		u--; v--;
		if(k >= n){
			printf("%lld\n",ans[n-1][u][v]);
		}
		else{
			printf("%lld\n",ans[k][u][v]);
		}
	}
	return 0;
}
