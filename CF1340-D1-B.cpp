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

const int N = 2000+5;

string v[] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};

int n;
int k;
int a[N];
int mask[11];
bool vis[N][N];
bool memo[N][N];
int choice[N][N];

bool DP(int pos, int left){
	if(pos == n) return left == 0;
	if(vis[pos][left]) return memo[pos][left];
	bool ans = false;
	for(int i=9; i>=0; i--){
		if((mask[i] & a[pos]) != a[pos]) continue;
		int changes = __builtin_popcount(a[pos] ^ mask[i]);
		if(left >= changes and DP(pos + 1, left - changes)){
			choice[pos][left] = i;
			ans = true;
			break;
		}
	}
	vis[pos][left] = true;
	return memo[pos][left] = ans;
}

int main(){
	ri2(n, k);
	char s[10];
	for(int i=0; i<10; i++){
		for(int j=0; j<v[i].size(); j++){
			if(v[i][j] == '1') mask[i] |= 1<<j;
		}
	}
	for(int i=0; i<n; i++){
		scanf("%s",s);
		for(int j=0; s[j]; j++){
			if(s[j] == '1') a[i] |= 1<<j;
		}
	}
	if(DP(0,k)){
		int left = k;
		for(int i=0; i<n; i++){
			putchar('0' + choice[i][left]);
			left -= __builtin_popcount(a[i] ^ mask[choice[i][left]]);
		}
		puts("");
	}
	else puts("-1");
	return 0;
}
