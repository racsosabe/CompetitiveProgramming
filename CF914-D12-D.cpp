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

const int N = 1000000+5;
const int LOG = 50;

int n;
int q;
int len;
int a[N];
int st[4*N];
iii inter[LOG];

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = a[l];
		return;
	}
	int mi = (l+r)/2;
	build(2*pos,l,mi);
	build(2*pos+1,mi+1,r);
	st[pos] = gcd(st[2*pos],st[2*pos+1]);
}

void update(int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = y;
		return;
	}
	int mi = (l+r)/2;
	if(l <= x and x <= mi) update(x,y,2*pos,l,mi);
	else update(x,y,2*pos+1,mi+1,r);
	st[pos] = gcd(st[2*pos],st[2*pos+1]);
}

int query(int x, int pos = 1, int l = 1, int r = n){
	if(l == r){
		return 1;
	}
	int mi = (l+r)/2;
	if((st[2*pos] % x != 0) and (st[2*pos+1] % x != 0)) return 2;
	return st[2*pos] % x != 0? query(x,2*pos,l,mi) : query(x,2*pos+1,mi+1,r);
}

void getIntervals(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y){
		inter[len++] = mp(pos,mp(l,r));
		return;
	}
	int mi = (l+r)/2;
	getIntervals(x,y,2*pos,l,mi);
	getIntervals(x,y,2*pos+1,mi+1,r);
}

bool possible(int x, int l, int r){
	int cnt = 0;
	int pos;
	int L;
	int R;
	for(int i=0; i<len; i++){
		if(st[inter[i].first] % x != 0){
			pos = inter[i].first;
			L = inter[i].second.first;
			R = inter[i].second.second;
			cnt++;
		}
		if(cnt > 1) return false;
	}
	if(cnt == 0) return true;
	return query(x,pos,L,R) == 1;
}

bool solve(int l, int r, int x){
	len = 0;
	getIntervals(l,r);
	return possible(x,l,r);
}

int main(){
	ri(n);
	for(int i=1; i<=n; i++){
		ri(a[i]);
	}
	build();
	ri(q);
	int op;
	int l, r, x;
	while(q--){
		ri(op);
		if(op == 1){
			ri3(l,r,x);
			puts(solve(l,r,x)?"YES":"NO");
		}
		else{
			ri2(l,r);
			update(l,r);
		}
	}
	return 0;
}
