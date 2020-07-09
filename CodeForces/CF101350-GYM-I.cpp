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

	- Ad-hoc + DP problem.

	- First set the valid characters in an array of booleans.

	- Second, compute the classic DP to check if substring [l,r] is a palindrome.

	- Third, try using all the valid characters as a l and iterate from r = l to

	  n-1 or until valid[r] is false.

	- Complexity: O(n^2) per testcase. It can be done in O(n) with manacher by

	  partitioning the string in all its valid substrings and computing the longest

	  palindrome in each of them.
*/

const int N = 1000+5;
const string mirrored = "AHIMOTUVWXY";

int n;
char s[N];
bool valid[N];
bool memo[N][N];

void clearAll(){
	for(int i=0; i<n; i++){
		valid[i] = false;
		for(int j=i; j<n; j++) memo[i][j] = false;
	}
}

int main(){
	int t;
	ri(t);
	while(t--){
		scanf("%s", s);
		n = strlen(s);
		for(int i=0; i<n; i++){
			if(mirrored.find(s[i]) != string::npos) valid[i] = true;
		}
		for(int i=0; i<n; i++){
			memo[i][i] = true;
		}
		for(int L=2; L<=n; L++){
			for(int i=0; i+L-1<n; i++){
				int j = i + L - 1;
				if(L == 2) memo[i][j] = s[i] == s[j];
				else memo[i][j] = (s[i] == s[j]) & memo[i+1][j-1];
			}
		}
		int ans = 0;
		for(int i=0; i<n; i++){
			if(valid[i]){
				for(int j = i; j < n; j++){
					if(!valid[j]) break;
					if(memo[i][j]) ans = max(ans, j - i + 1);
				}
			}
		}
		printf("%d\n", ans);
		if(t) clearAll();
	}
	return 0;
}
