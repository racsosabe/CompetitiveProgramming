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
const long long MOD = (1LL<<61) - 1;

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
	return a + b < m? a + b : a + b - m;
}

ll mul(ll a, ll b, ll m = MOD){
	ll res = 0LL;
	while(b > 0){
		if(b & 1) res = add(res, a, m);
		a = add(a, a, m);
		b >>= 1;
	}
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

const int N = 2000+5;
const int M = 200+5;
const int B = 311;

int n, m;
ll pot[N];
ll poti[N];
char a[N][M];
char b[M][N];
ll prefixA[N];
ll hashes[M][N];
ll prefixB[M][N];

void init(){
	pot[0] = 1;
	for(int i=1; i<N; i++) pot[i] = mul(pot[i-1], B);
	poti[N-1] = pow_mod(pot[N-1], MOD-2);
	for(int i=N-2; i>=0; i--){
		poti[i] = mul(B, poti[i+1]);
	}
}

int main(){
	ri2(n, m);
	init();
	for(int i=0; i<n; i++){
		scanf("%s",a[i]);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			prefixA[i] = add(prefixA[i], mul(pot[j], a[i][j]- 'a' + 1));
		}
	}
	for(int i=0; i<m; i++){
		scanf("%s",b[i]);
		for(int j=0; j<n; j++){
			prefixB[i][j+1] = add(prefixB[i][j], mul(pot[j+1], b[i][j] - 'a' + 1));
		}
		for(int j=0; j<n; j++){
			if(j + m - 1 < n){
				hashes[i][j] = mul(poti[j+1], add(prefixB[i][j + m], MOD - prefixB[i][j]));
			}
			else break;
		}
	}
	for(int i = 0; i + m - 1 < n; i++){
		for(int j = 0; j + m - 1 < n; j++){
			bool valid = true;
			for(int k = 0; k < m and valid; k++){
				if(prefixA[i + k] != hashes[k][j]) valid = false;
			}
			if(valid){
				printf("%d %d\n", i+1, j+1);
				return 0;
			}
		}
	}
	assert(false);
	return 0;
}
