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
		- DP & Two Pointers problem.

		- First of all, use cumulative sums to get the number of 'a's
		  Then, we can notice that if we fixed upper row and lower row
		  we will only need to get the pairs of cols that work.

		- To get the pairs of cols, first compute for each col if

		  table[f1][j] == table[f2][j] and then add it to a vector

		  G[table[f1][j]-'a'] <- j

		  Notice that the sum of vectors' sizes will be O(M)

		- Finally, for each vector, we can use two pointers to get the intervals
		  that work for each fixed col.

		- Complexity: O(n^2 m)

*/

const int N = 400+5;
const int E = 26 + 2;

int n, m, k;
char table[N][N];
int ac[N][N];

bool can(int f1, int c1, int f2, int c2){
	int act = 0;
	act += ac[f2][c2];
	act += ac[f1-1][c1-1];
	act -= ac[f1-1][c2];
	act -= ac[f2][c1-1];
	return act <= k;
}

ll solve(int f1, int f2){
	ll ans = 0LL;
	vi positions[E];
	for(int i=1; i<=m; i++){
		if(table[f1][i] == table[f2][i]){
			positions[table[f1][i]-'a'].pb(i);
		}
	}
	for(int i=0; i<26; i++){
		for(int j=0; j<positions[i].size(); j++){
		}
	}
	for(int i=0; i<26; i++){
		int p = 0;
		for(int j=0; j<positions[i].size(); j++){
			p = max(p,j+1);
			while(p < positions[i].size() and can(f1,positions[i][j],f2,positions[i][p])){
				p++;
			}
			p--;
			ans += p - j;
		}
	}
	return ans;
}

int main(){
	freopen("input.txt","r",stdin);
	ri3(n,m,k);
	char c;
	getchar();
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			c = getchar();
			table[i][j] = c;
			if(c == 'a') ac[i][j] = 1;
			ac[i][j] += ac[i-1][j];
			ac[i][j] += ac[i][j-1];
			ac[i][j] -= ac[i-1][j-1];
		}
		getchar();
	}
	ll ans = 0;
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			ans += solve(i,j);
		}
	}
	freopen("output.txt","w",stdout);
	cout << ans << endl;
	return 0;
}
