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

const int N = 1000000 + 5;

int n;
int a, b, c;
long long x[N];
long long s[N];
long long memo[N];

struct line{
	long long m;
	long long b;
	line(){}
	line(long long m, long long b) : m(m), b(b) {}
};

vector<line> CHT;

bool better(line l1, line l2, line l3){
	return (l3.b - l1.b) * (l1.m - l2.m) <= (l2.b - l1.b) * (l1.m - l3.m);
}

void addLine(line x){
	int len = CHT.size();
	while(len >= 2 and better(CHT[len - 2], CHT[len - 1], x)) len -= 1;
	CHT.resize(len);
	CHT.emplace_back(x);
}

long long f(int pos, int x){
	return CHT[pos].m * x + CHT[pos].b;
}

long long getMax(int x){
	int lo = 0, hi = CHT.size() - 1;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(f(mi, x) < f(mi + 1, x)) lo = mi + 1;
		else hi = mi;
	}
	return f(lo, x);
}

long long solve(){
	addLine(line(0, 0));
	for(int i = 1; i <= n; i++){
		memo[i] = a * s[i] * s[i] + b * s[i] + c + getMax(s[i]);
		addLine(line(-2 * a * s[i], memo[i] + a * s[i] * s[i] - b * s[i]));
	}
	return memo[n];
}

int main(){
	scanf("%d", &n);
	scanf("%d %d %d", &a, &b, &c);
	for(int i = 1; i <= n; i++){
		scanf("%lld", x + i);
	}
	for(int i = 1; i <= n; i++){
		s[i] = s[i - 1] + x[i];
	}
	printf("%lld\n", solve());
	return 0;
}
