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

const int N = 100000+5;

int n;
int p[N];
int pos[N];
int cnt[N];
int par[N];
int st[4*N];

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

void update(int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2*pos, l, mi);
	else update(x, y, 2*pos+1, mi+1, r);
	st[pos] = max(st[2*pos], st[2*pos+1]);
}

int query(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return -1;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return max(query(x, y, 2*pos, l, mi), query(x, y, 2*pos+1, mi+1, r));
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(a > b) swap(a, b);
	par[a] = b;
	cnt[b] += cnt[a];
	cnt[a] = 0;
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri(n);
		for(int i=1; i<=n; i++){
			ri(p[i]);
			pos[p[i]] = i;
			cnt[i] = 1;
			par[i] = i;
			update(i, 1);
		}
		par[n+1] = n+1;
		int maximum = 1;
		bool can = true;
		for(int i=1; i<=n; i++){
			int id = pos[i];
			if(cnt[id] == maximum){
				join(id, id + 1);
				update(id, 0);
				if(par[id] <= n){
					update(par[id], cnt[par[id]]);
				}
				maximum = st[1];
			}
			else can = false;
		}
		puts(can?"Yes":"No");
	}
	return 0;
}
