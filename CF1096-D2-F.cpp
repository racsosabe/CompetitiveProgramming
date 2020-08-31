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
const int MOD = 998244353;

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

int add(int a, int b, int m = MOD){
	return (a + b) % m;
}

int mul(ll a, ll b, int m = MOD){
	return (a * b) % m;
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
int m;
int p[N];
int f[N];
int ft[N];
int ac[N];
int ac2[N];
bool vis[N];

void update(int pos, int val){
	pos++;
	while(pos <= n + 1){
		ft[pos] += val;
		pos += (-pos) & pos;	
	}
}

int getSum(int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

int getUtoK(){
	for(int i = 1; i <= n; i++){
		if(!vis[i]) ac2[i] = 1;
		ac2[i] += ac2[i - 1];
	}
	int cur_m = 0;
	int res = 0;
	int invm = pow_mod(m, MOD - 2);
	for(int i = 1; i <= n; i++){
		if(p[i] == -1){
			cur_m += 1;
			continue;
		}
		res = add(res, mul(cur_m, mul(m - ac2[p[i]], invm)));
	}
	cur_m = 0;
	for(int i = n; i >= 1; i--){
		if(p[i] == -1){
			cur_m += 1;
			continue;
		}
		res = add(res, mul(cur_m, mul(ac2[p[i] - 1], invm)));
	}
	return res;
}

int solve(){
	int fixed = 0;
	for(int i = 1; i <= n; i++){
		if(p[i] == -1){
			m += 1;
			continue;
		}
		vis[p[i]] = true;
		fixed = add(fixed, i - m - 1 - getSum(p[i]));
		update(p[i], 1);
	}
	int inv2 = (MOD + 1) / 2;
	int unknowns = mul(m, mul(add(m, MOD - 1), mul(inv2, inv2)));
	int utok = getUtoK();
	int ans = add(fixed, add(unknowns, utok));
	return ans;
}

int main(){
	ri(n);
	for(int i = 1; i <= n; i++) ri(p[i]);
	f[0] = 1;
	for(int i = 1; i <= n; i++) f[i] = mul(f[i - 1], i);
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
