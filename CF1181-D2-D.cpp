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

const int N = 500000 + 5;
const ll inf = 1e18 + 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int val;
	int cnt;
	int priority;
	node* left;
	node* right;
	node(int val) : val(val) {
		cnt = 1;
		priority = random(0, 1e9);
		left = right = nullptr;
	}
};

int n;
int m;
int q;
ll v[N];
node* T;
int f[N];
int ans[N];

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void update(node* t){
	if(t) t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
}

node* merge(node* l, node* r){
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	if(l -> priority > r -> priority){
		l -> right = merge(l -> right, r);
		update(l);
		return l;
	}
	else{
		r -> left = merge(l, r -> left);
		update(r);
		return r;
	}
}

pair<node*, node*> split(node* t, int x){
	if(t == nullptr){
		return {nullptr, nullptr};
	}
	if(t -> val <= x){
		pair<node*, node*> p = split(t -> right, x);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, x);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

node* insert(node* u, int x){
	pair<node*, node*> p = split(u, x);
	u = merge(p.first, new node(x));
	u = merge(u, p.second);
	return u;
}

int getKth(node* u, int k){
	if(k == cnt(u -> left) + 1) return u -> val;
	if(k <= cnt(u -> left)) return getKth(u -> left, k);
	return getKth(u -> right, k - cnt(u -> left) - 1);
}

void solve(){
	vector<int> p(m);
	iota(all(p), 1);
	sort(all(p), [&] (int i, int j){
		if(f[i] == f[j]) return i < j;
		return f[i] < f[j];
	});
	vector<int> queries(q);
	iota(all(queries), 0);
	sort(all(queries), [&] (int i, int j){
		return v[i] < v[j];
	});
	ll curL = 1;
	int pos = 0;
	for(int i = 0; i < m; i++){
		T = insert(T, p[i]);
		ll nxt = i + 1 < m ? curL + 1LL * (i + 1) * (f[p[i + 1]] - f[p[i]]) : inf;
		while(pos < q and v[queries[pos]] - n < nxt){
			int x = queries[pos];
			ll k = v[x] - n;
			k -= curL;
			k %= (i + 1);
			ans[x] = getKth(T, k + 1);
			pos += 1;
		}
		curL = nxt;
	}
}

int main(){
	ri3(n, m, q);
	for(int i = 1; i <= n; i++){
		int x;
		ri(x);
		f[x] += 1;
	}
	for(int i = 0; i < q; i++){
		rll(v[i]);
	}
	solve();
	for(int i = 0; i < q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
