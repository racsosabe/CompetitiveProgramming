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

/*
	Autor: Racso Galvan

	Idea:

	- Programación Dinámica

	- Basta con definir una recursión DP(pos, happy, full) que dará la máxima cantidad

	  de platos a comer dado que hemos considerado los primeros "pos" platos

	  y hemos elegido de manera que nuestra felicidad es mayor o igual a "happy"

	  y tenemos una llenura "full".

	- Para no usar mucha memoria, notemos que nuestra condición para que una 

	  serie de elecciones sea válida es que happy >= 100, así que cuando hacemos

	  una elección, el happy del nuevo estado es min(happy + f[pos], 100).

	- Complejidad: O(n * max_felicidad * max_llenura).
*/

const int N = 51;
const int M = 101;

int n;
int l[N];
int f[N];
bool vis[N][M][M];
int memo[N][M][M];

int DP(int pos, int happy, int full){
	if(pos == n){
		return happy == 100? 0 : -100;
	}
	if(vis[pos][happy][full]) return memo[pos][happy][full];
	int ans = DP(pos + 1, happy, full);
	if(full + l[pos] <= 100){
		ans = max(ans, 1 + DP(pos + 1, min(happy + f[pos], 100), full + l[pos]));
	}
	vis[pos][happy][full] = true;
	return memo[pos][happy][full] = ans;
}

int main(){
	ri(n);
	for(int i = 0; i < n; i++){
		ri2(l[i], f[i]);
	}
	printf("%d\n", DP(0, 0, 0));
	return 0;
}
