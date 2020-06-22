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
const int inf = 1e9;

int n;
char s[N];
int nxt[N];
ii st[4*N];
int par[N];
int memo[N];
int choice[N];

void build(int pos = 1, int l = 0, int r = n-1){
	if(l == r){
		st[pos].first = inf;
		st[pos].second = l;
		return;
	}
	int mi = (l + r) / 2;
	build(2*pos, l, mi);
	build(2*pos+1, mi+1, r);
	st[pos] = min(st[2*pos], st[2*pos+1]);
}

void update(int x, int y, int pos = 1, int l = 0, int r = n-1){
	if(l == r){
		st[pos].first = y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2*pos, l, mi);
	else update(x, y, 2*pos+1, mi+1, r);
	st[pos] = min(st[2*pos], st[2*pos+1]);
}

ii query(int x, int y, int pos = 1, int l = 0, int r = n-1){
	if(y < l or r < x or x > y) return mp(inf, -1);
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return min(query(x, y, 2*pos, l, mi), query(x, y, 2*pos+1, mi+1, r));
}

int main(){
	scanf("%s",s);
	n = strlen(s);
	reverse(s, s + n);
	s[n] = '0';
	n += 1;
	s[n] = '\0';
	int last = 0;
	for(int i=0; i<n; i++){
		if(s[i] == '0'){
			last = i + 1;
		}
		nxt[i] = last;
	}
	build();
	for(int i=0; i<n; i++){
		memo[i] = (i > 0? memo[i-1] : 0) + s[i] - '0';
		par[i] = i-1;
		choice[i] = 1;
		if(s[i] == '0' and s[i-1] == '1'){
			ii before = query(nxt[i-1], i-1);
			if(memo[i] > 1 + before.first){
				memo[i] = 1 + before.first;
				par[i] = before.second;
				choice[i] = -1;
			}
		}
		update(i, 1 + (i > 0? memo[i-1] : 0));
	}
	printf("%d\n",memo[n-1]);
	int pos = n-1;
	while(pos >= 0){
		if(choice[pos] == 1){
			if(s[pos] == '1'){
				printf("+2^%d\n",pos);
			}
			pos = par[pos];
		}
		else{
			printf("+2^%d\n",pos);
			pos = par[pos];
			printf("-2^%d\n",pos);
			pos--;
		}
	}
	return 0;
}
