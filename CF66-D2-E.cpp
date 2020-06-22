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

const int N = 200000+5;

int n;
int len;
int a[N];
int b[N];
ll st[4*N];
bool can[N];
ll lazy[4*N];
ll prefixA[N];
ll prefixB[N];

void build(int pos = 1, int l = 0, int r = len - 1){
	lazy[pos] = 0LL;
	if(l == r){
		st[pos] = prefixA[l] - prefixB[l];
		return;
	}
	int mi = (l + r) / 2;
	build(2*pos, l, mi);
	build(2*pos+1, mi+1, r);
	st[pos] = min(st[2*pos],st[2*pos+1]);
}

void push(int pos, int l, int r){
	if(lazy[pos]){
		st[pos] += lazy[pos];
		if(l < r){
			lazy[2*pos] += lazy[pos];
			lazy[2*pos+1] += lazy[pos];
		}
		lazy[pos] = 0LL;
	}
}

void update(int x, int y, int z, int pos = 1, int l = 0, int r = len-1){
	push(pos, l, r);
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y){
		lazy[pos] += z;
		push(pos, l, r);
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, z, 2*pos, l, mi);
	update(x, y, z, 2*pos+1, mi+1, r);
	st[pos] = min(st[2*pos], st[2*pos+1]);
}

ll query(int x, int y, int pos = 1, int l = 0, int r = len - 1){
	push(pos, l, r);
	if(y < l or r < x or x > y) return LLONG_MAX;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return min(query(x, y, 2*pos, l, mi), query(x, y, 2*pos+1, mi+1, r));
}

void solve(bool reversed){
	for(int i=0; i<len; i++){
		prefixA[i] = a[i % n];
		if(i > 0) prefixA[i] += prefixA[i-1];
		prefixB[i] = b[i % n];
		if(i > 0) prefixB[i] += prefixB[i-1];
	}
	build();
	for(int i=0; i<n; i++){
		if(query(i, i + n - 1) >= 0){
			can[reversed? n - 1 - i : i] = true;
		}
		update(i + 1, len - 1, b[i] - a[i]);
	}
}

int main(){
	ri(n);
	len = n + n;
	for(int i=0; i<n; i++){
		ri(a[i]);
	}
	for(int i=0; i<n; i++){
		ri(b[i]);
	}
	solve(0);
	vector<int> new_b(n);
	for(int i=0; i<n; i++){
		new_b[i + 1 < n? i + 1 : 0] = b[i];
	}
	for(int i=0; i<n; i++){
		b[i] = new_b[i];
	}
	reverse(a, a + n);
	reverse(b, b + n);
	solve(1);
	vector<int> ans;
	for(int i=0; i<n; i++){
		if(can[i]) ans.emplace_back(i+1);
	}
	printf("%d\n",(int)ans.size());
	for(int i=0; i<ans.size(); i++){
		printf("%d%c",ans[i]," \n"[i + 1 == ans.size()]);
	}
	return 0;
}
