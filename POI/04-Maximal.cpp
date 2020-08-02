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

	- Number Theory and DP problem.

	- We want to generate a set of integers a_{i} such that:

	  LCM(a) is maximum and sum(a) = n.

	- Notice that the lexicographically minimum permutation will be the join of 
	
	  contiguous cycles of length a_{i} (sorted) and shifted once to the left.

	- We want to maximize the LCM but achieving the lexicographically minimum

	  sequence of lengths a.

	- We can just use a_{i} = 1 or a power of a prime for all i and that's enough

	  to get the wanted answer.

	- Rebuild the answer in O(n).

	- Complexity: O(n^2)
*/

const int MAX = 1e4 + 5;
const int PRIMES = 300;

int n;
vi primos;
int pf[MAX];
int ans[MAX];
int choice[PRIMES][MAX];
double memo[PRIMES][MAX];

void init(){
	for(int i=2; i<MAX; i++){
		if(pf[i] == 0){
			pf[i] = i;
			primos.emplace_back(i);
		}
		for(int p : primos){
			if(i * p >= MAX) break;
			if(p > pf[i]) break;
			pf[i * p] = p;
		}
	}
}

double DP(int pos, int left){
	if(pos == PRIMES) return 0.0;
	if(primos[pos] > left) return 0.0;
	if(memo[pos][left] > -10) return memo[pos][left];
	double ans = DP(pos+1,left);
	choice[pos][left] = -1;
	int value = primos[pos];
	double factor = log(primos[pos]);
	for(int i = 1; value <= left; i++){
		double cand = i * factor + DP(pos+1, left - value);
		if(ans < cand){
			ans = cand;
			choice[pos][left] = value;
		}
		value *= primos[pos];
	}
	return memo[pos][left] = ans;
}

void preprocess(){
	for(int i=0; i<PRIMES; i++){
		for(int j=0; j<MAX; j++){
			memo[i][j] = -1e9;
		}
	}
}

int main(){
	init();
	int t;
	ri(t);
	preprocess();
	while(t--){
		ri(n);
		double res = DP(0,n);
		vector<int> cycles;
		int pos = 0;
		int left = n;
		while(true){
			if(pos == PRIMES) break;
			if(primos[pos] > left) break;
			if(choice[pos][left] != -1){
				cycles.emplace_back(choice[pos][left]);
				left -= choice[pos][left];
			}
			pos += 1;
		}
		while(left > 0){
			cycles.emplace_back(1);
			left -= 1;
		}
		sort(all(cycles));
		int L = 1;
		for(auto x : cycles){
			int R = L + x - 1;
			for(int i = L; i <= R; i++){
				ans[i] = i + 1 <= R ? i + 1 : L;
			}
			L += x;
		}
		for(int i=1; i<=n; i++){
			printf("%d%c",ans[i]," \n"[i == n]);
		}
	}
	return 0;
}
