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

const int N = 1000+5;

int n, m;
char a[N];
char b[N];
bool vis[N][N];
int memo[N][N];
int choice[N][N];

// 0 -> replace / nothing according to a[i] != b[j]
// 1 -> insert
// 2 -> delete

int DP(int i, int j){
	if(i == n and j == m) return 0;
	if(vis[i][j]) return memo[i][j];
	vis[i][j] = true;
	if(i == n){
		choice[i][j] = 1;
		return memo[i][j] = 1 + DP(i, j + 1);
	}
	if(j == m){
		choice[i][j] = 2;
		return memo[i][j] = 1 + DP(i + 1, j);
	}
	int ans = (a[i] != b[j]) + DP(i + 1, j + 1);
	if(1 + DP(i, j + 1) < ans){
		ans = 1 + DP(i, j + 1);
		choice[i][j] = 1;
	}
	if(1 + DP(i + 1, j) < ans){
		ans = 1 + DP(i + 1, j);
		choice[i][j] = 2;
	}
	return memo[i][j] = ans;
}

int main(){
	scanf("%s %s",a,b);
	n = strlen(a);
	m = strlen(b);
	int ans = DP(0,0);
	printf("%d\n", ans);
	int i = 0, j = 0;
	int len = 0;
	while(i < n or j < m){
		if(choice[i][j] == 0){
			if(a[i] != b[j]){
				printf("REPLACE %d %c\n",len + 1, b[j]);
			}
			len += 1;
			i += 1;
			j += 1;
		}
		if(choice[i][j] == 1){
			printf("INSERT %d %c\n", len + 1, b[j]);
			j += 1;
			len += 1;
		}
		if(choice[i][j] == 2){
			printf("DELETE %d\n", len + 1);
			i += 1;
		}
	}
	return 0;
}
