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

const int N = 50;

int n;
int k;
ll a[N];
ll L, R;
vll m1[N], m2[N];

void getValues(int len, int start, int type){
	vll memo(1<<len, 0LL);
	for(int i = 1; i < 1<<len; i++){
		int nxt = 31 - __builtin_clz(i);
		int prv = i ^ (1<<nxt);
		memo[i] = memo[prv] + a[nxt + start];
	}
	for(int i = 0; i < 1<<len; i++){
		if(type == 0){
			m1[__builtin_popcount(i)].emplace_back(memo[i]);
		}
		else{
			m2[__builtin_popcount(i)].emplace_back(memo[i]);
		}
	}
	for(int i = 0; i < n; i++){
		if(type == 0) sort(all(m1[i]));
		else sort(all(m2[i]));
	}
}

void preprocess(){
	int l1 = n / 2;
	int l2 = n - l1;
	getValues(l1, 0, 0);
	getValues(l2, l1, 1);
}

ll solve(int p1, int p2, ll max_val){
	int pos = m2[p2].size() - 1;
	ll res = 0LL;
	for(int i = 0; i < m1[p1].size(); i++){
		while(pos >= 0 and m1[p1][i] + m2[p2][pos] > max_val) pos -= 1;
		res += pos + 1;
	}
	return res;
}

ll f(ll X){
	ll ans = 0LL;
	for(int i = 0; i <= k; i++){
		int j = k - i;
		ans += solve(i, j, X);
	}
	return ans;
}

int main(){
	ri2(n, k);
	rll2(L, R);
	for(int i = 0; i < n; i++) rll(a[i]);
	preprocess();
	printf("%lld\n", f(R) - f(L - 1));
	return 0;
}
