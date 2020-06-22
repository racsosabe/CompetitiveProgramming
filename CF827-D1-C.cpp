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
const int E = 256;

int n;
int q;
int a[N];
char s[N];
char e[12];
char id[E];
int ft[11][11][N][4];

void update(int id, int res, int pos, int c, int val){
	pos++;
	while(pos <= n){
		ft[id][res][pos][c] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int id, int res, int pos, int c){
	pos++;
	int ans = 0;
	while(pos > 0){
		ans += ft[id][res][pos][c];
		pos &= pos-1;
	}
	return ans;
}

int query(int id, int res, int L, int R, int c){
	return getSum(id, res, R, c) - getSum(id, res, L-1, c);
}

void modify(int pos, int c){
	for(int len = 1; len <= 10; len++){
		int res = pos % len;
		int last = a[pos];
		update(len, res, pos, last, -query(len, res, pos, pos, last));
		update(len, res, pos, c, 1);
	}
	a[pos] = c;
}

int solve(int l, int r, int len){
	int ans = 0;
	for(int res = 0; res < len; res++){
		int res2 = (l + res) % len;
		ans += query(len, res2, l, r, id[e[res]]);
	}
	return ans;
}

int main(){
	scanf("%s",s);
	n = strlen(s);
	id['A'] = 0;
	id['T'] = 1;
	id['G'] = 2;
	id['C'] = 3;
	for(int i = 0; i < n; i++){
		modify(i, id[s[i]]);
	}
	ri(q);
	char c;
	int op, l, r;
	while(q--){
		ri(op);
		if(op == 1){
			scanf("%d %c",&l, &c);
			l--;
			modify(l, id[c]);
		}
		else{
			ri2(l, r);
			scanf("%s",e);
			l--; r--;
			printf("%d\n", solve(l, r, strlen(e)));
		}
	}
	return 0;
}
