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

const int N = 20;

ll k;
int n;
int len;
int a[N];
int c[N];
int x[N];
int M[N][N];
int R[N][N];
int C[N][N];

void init(int p, int q, int r){
	for(int i = 0; i < n; i++){
		M[0][i] = c[i + 1];
	}
	M[0][n] = r;
	M[0][n+1] = q;
	M[0][n+2] = p;
	for(int i = 1; i < n; i++){
		M[i][i-1] = 1;
	}
	M[n][len - 1] = M[n][len - 3] = 1;
	M[n][len - 2] = 2;
	M[n + 1][len - 1] = M[n + 1][len - 2] = 1;
	M[n + 2][n + 2] = 1;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			R[i][j] = i == j;
		}
	}
}

void multiply(int type){
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			C[i][j] = 0;
			for(int k = 0; k < len; k++){
				if(type) C[i][j] = add(C[i][j], mul(R[i][k], M[k][j]));
				else C[i][j] = add(C[i][j], mul(M[i][k], M[k][j]));
			}
		}
	}
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			if(type) R[i][j] = C[i][j];
			else M[i][j] = C[i][j];
		}
	}
}

void fastexpo(ll b){
	while(b > 0){
		if(b & 1) multiply(1);
		multiply(0);
		b >>= 1;
	}
}

int main(){
	ri(n);
	rll(k);
	len = n + 3;
	for(int i = 0; i < n; i++) ri(a[i]);
	for(int i = 1; i <= n; i++) ri(c[i]);
	int p, q, r;
	ri3(p, q, r);
	if(k < n){
		printf("%d\n", a[k]);
	}
	else{
		init(p, q, r);
		fastexpo(k - n + 1);
		for(int i = 0; i < n; i++){
			x[i] = a[n - 1 - i];
		}
		x[n] = mul(n, n);
		x[n+1] = n;
		x[n+2] = 1;
		int ans = 0;
		for(int i = 0; i < len; i++){
			ans = add(ans, mul(R[0][i], x[i]));
		}
		printf("%d\n", ans);
	}
	return 0;
}
