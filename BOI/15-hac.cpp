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

	- Min Queue problem.

	- Just notice that if we start in a computer i, then the final answer will

	  be a contiguous cyclic range that contains i and has length ceil(n / 2).

	- Now, since the computer plays optimally, it can just choose an optimal

	  
	  position such that we can't go further from it, thus making us take some

	  fixed range after all.

	- So, the answer starting in computer i is the minimum of such ranges.

	- If we use a Min Queue to mantain the minimum of all those precomputed ranges'

	  values, we achieve a linear complexity.

	- Complexity: O(n)
*/

const int N = 1500000+5;

int n;
int a[N];
ll ac[N];
int len[2];
int res[N];
int st1[2][N];
int st2[2][N];

void insert(int x){
	len[0]++;
	st1[0][len[0]] = x;
	st1[1][len[0]] = min(st1[1][len[0]-1], x);
}

void remove(){
	if(!len[1]){
		for(int j = len[0]; j >= 1; j--){
			len[1]++;
			int x = st1[0][j];
			st2[0][len[1]] = x;
			st2[1][len[1]] = min(x, st2[1][len[1]-1]);
		}
		len[0] = 0;
	}
	len[1] -= 1;
}

int getMin(){
	return min(st2[1][len[1]], st1[1][len[0]]);
}

int main(){
	ri(n);
	for(int i = 1; i <= n; i++){
		ri(a[i]);
		ac[i] = ac[i-1] + a[i];
	}
	for(int i = n+1; i <= n+n+n; i++){
		a[i] = a[i - n];
		ac[i] = ac[i - 1] + a[i];
	}
	int moves = (n + 1) / 2;
	for(int i = 1; i + moves - 1 <= n+n+n; i++){
		res[i] = ac[i + moves - 1] - ac[i - 1];
	}
	int ans = 0;
	st1[0][0] = st2[0][0] = st1[1][0] = st2[1][0] = 2e9;
	for(int i = n + 2 - moves; i <= n; i++){
		insert(res[i]);
	}
	for(int i = n + 1; i <= n + n; i++){
		insert(res[i]);
		if(i - moves >= n + 2 - moves) remove();
		ans = max(ans, getMin());
	}
	printf("%d\n", ans);
	return 0;
}
