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

	- Observation problem

	- It can be proved that the solution always starts in [1, 3] or ends in [n - 3, n]

	  This can be done by contradiction and analyzing all the possible cases(exhaustive).

	- Complexity: O(n) using prefix sums for each letter.
*/

const int N = 1000000+5;

int n;
int a[3];
char s[N];
int prefix[3][N];

int id(char c){
	if(c == 'S') return 0;
	return c - 'A';
}

bool test(int L, int R){
	for(int i=0; i<3; i++){
		a[i] = prefix[i][R] - prefix[i][L-1];
	}
	for(int i=0; i<3; i++){
		for(int j=i+1; j<3; j++){
			if(a[i] == a[j] and a[i] > 0) return false;
		}
	}
	return true;
}

int main(){
	ri(n);
	scanf("%s",s + 1);
	for(int i=1; i<=n; i++){
		prefix[id(s[i])][i] = 1;
		for(int j=0; j<3; j++) prefix[j][i] += prefix[j][i-1];
	}
	int ans = 0;
	for(int l = 1; l <= min(3, n); l++){
		for(int r = l; r <= n; r++){
			if(r - l + 1 <= ans) continue;
			if(test(l, r)) ans = r - l + 1;
		}
	}
	for(int r = max(1, n - 2); r <= n; r++){
		for(int l = 1; l <= r; l++){
			if(r - l + 1 <= ans) continue;
			if(test(l, r)) ans = r - l + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
