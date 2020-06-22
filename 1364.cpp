#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<utility>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
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

const int E = 100+5;
const int N = 100+5;
const int inf = 1<<30;

int n;
int m;
int len;
int D[N];
int u[E];
int v[E];
int w[E];

void addEdge(int i, int j, int we){
	u[len] = j;
	v[len] = i;
	w[len] = we;
	len += 1;
}

bool Bellman(){
	for(int i=0; i<=n; i++){
		D[i] = 0;
	}
	bool relaxed;
	for(int i=0; i<=n; i++){
		relaxed = false;
		for(int j=0; j<len; j++){
			if(D[v[j]] > D[u[j]] + w[j]){
				D[v[j]] = D[u[j]] + w[j];
				relaxed = true;
			}
		}
		if(!relaxed) break;
	}
	return !relaxed;
}

int main(){
	char s[5];
	while(ri(n) == 1 and n){
		ri(m);
		len = 0;
		int l, r, we;
		for(int i=0; i<m; i++){
			ri2(l, r);
			r += l;
			l -= 1;
			scanf("%s",s);
			ri(we);
			if(s[0] == 'g'){
				addEdge(l, r, -(we + 1));
			}
			else{
				addEdge(r, l, we - 1);
			}
		}
		puts(Bellman()?"lamentable kingdom":"successful conspiracy");
	}
	return 0;
}
