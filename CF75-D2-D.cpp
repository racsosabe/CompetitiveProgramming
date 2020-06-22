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

struct node{
	ll sum;
	ll ans;
	ll prefix;
	ll suffix;
	node(){};
	node(ll sum, ll ans, ll prefix, ll suffix) :
		sum(sum), ans(ans), prefix(prefix), suffix(suffix) {};
};

const int N = 250000+5;

int n;
int m;
int id[N];
ll sum[N];
ll ans[N];
ll prefix[N];
ll suffix[N];

node merge(node a, node b){
	node q;
	q.sum = a.sum + b.sum;
	q.ans = max({a.ans, b.ans, a.suffix + b.prefix});
	q.prefix = max(a.prefix, a.sum + b.prefix);
	q.suffix = max(b.suffix, b.sum + a.suffix);
	return q;
}

node solve(int l, int r){
	if(l == r){
		return node(sum[id[l]], ans[id[l]], prefix[id[l]], suffix[id[l]]);
	}
	int mi = (l + r) / 2;
	node L = solve(l, mi);
	node R = solve(mi + 1, r);
	return merge(L, R);
}

int main(){
	ri2(n, m);
	for(int i=1; i<=n; i++){
		int q;
		ri(q);
		ans[i] = LLONG_MIN;
		sum[i] = 0LL;
		prefix[i] = suffix[i] = LLONG_MIN;
		vector<ll> v(q);
		ll mini = 0LL;
		ll p = 0LL;
		for(int j=0; j<q; j++){
			rll(v[j]);
			sum[i] += v[j];
			p += v[j];
			ans[i] = max(ans[i], p - mini);
			mini = min(mini, p);
			prefix[i] = max(prefix[i], p);
		}
		for(int j=q-1; j>=0; j--){
			if(j + 1 < q) v[j] += v[j+1];
			suffix[i] = max(suffix[i], v[j]);
		}
	}
	for(int i=1; i<=m; i++){
		ri(id[i]);
	}
	node ans = solve(1, m);
	printf("%lld\n",ans.ans);
	return 0;
}
