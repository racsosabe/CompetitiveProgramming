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
		- Meet in the Middle problem.

		- First of all, notice that m is small enough so that a complexity of
		  O(n 2^(m/2) m) will pass.

		- After it, also realize that we can preprocess a counter to relate
		  the first 8 bits and the last 8 bits of the numbers.

		- Thus, create a counter cnt[i][j][k] that will store the number of
		  values such that the last 8 bits are equal to j and the first 8 bits
		  differ from i in k positions (Hamming distance).

		- Now, to compute the answer, set an array ans[m+1] so that you
		
		  can brute force the values for each j in [0,2^8> and k in [0,8].
  		  ans[k + d(last 8 bits of x,j)] += cnt[first 8 bits of x][j][k]

		- Complexity: O(n 2^(m/2) m + 2^m). The 2^m is for preprocessing Hamming Distance.
*/

const int N = 200000+5;
const int M = 16 + 5;
const int MAX = (1<<8)+5;

int n, m;
int ans[M];
int d[MAX][MAX];
int cnt[MAX][MAX][M];

void init(){
	for(int i=0; i<1<<8; i++){
		for(int j=0; j<1<<8; j++){
			d[i][j] = __builtin_popcount(i^j);
		}
	}
}

int main(){
	init();
	ri2(n,m);
	int x;
	const int limit = 1<<8;
	for(int i=0; i<n; i++){
		ri(x);
		memset(ans,0,sizeof ans);
		for(int j=0; j<1<<8; j++){
			for(int k=0; k<=8; k++){
				ans[k+d[x>>8][j]] += cnt[x%limit][j][k];
			}
		}
		printf("%d",ans[0]);
		for(int j=1; j<=m; j++){
			printf(" %d",ans[j]);
		}
		puts("");
		for(int j=0; j<limit; j++){
			cnt[j][x >> 8][d[x % limit][j]]++;
		}
	}
	return 0;
}
