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

int add(int a, int b, int m = MOD){
	return (a + b < m ? a + b : a + b - m);
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

const int N = 200 + 5;
const int LOG = 31;

struct matrix{
	int n;
	int m;
	vector< vector<int> > M;

	matrix(){};

	void set(int _n, int _m){
		n = _n;
		m = _m;
		M.resize(n);
		for(int i = 0; i < n; i++){
			M[i].resize(m);
			for(int j = 0; j < m; j++){
				M[i][j] = 0;
			}
		}
	}

	matrix operator * (matrix b){
		assert(m == b.n);
		matrix q;
		q.set(n, b.m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < b.m; j++){
				for(int k = 0; k < m; k++){
					q.M[i][j] = add(q.M[i][j], mul(M[i][k], b.M[k][j]));
				}
			}
		}
		return q;
	}

	matrix operator + (matrix b){
		assert(n == b.n and m == b.m);
		matrix q;
		q.set(n, m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				q.M[i][j] = add(M[i][j], b.M[i][j]);
			}
		}
		return q;
	}

	void identity(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				M[i][j] = (i == j);
			}
		}
	}

	void operator *= (matrix b){
		assert(m == b.n);
		vector<vi> q(n, vector<int>(b.m, 0));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < b.m; j++){
				q[i][j] = 0;
				for(int k = 0; k < m; k++){
					q[i][j] = add(q[i][j], mul(M[i][k], b.M[k][j]));
				}
			}
		}
		m = b.m;
		M = q;
	}

	void operator += (matrix b){
		assert(n == b.n and m == b.m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				M[i][j] = add(M[i][j], b.M[i][j]);
			}
		}
	}

	void operator = (matrix b){
		n = b.n;
		m = b.m;
		M = b.M;
	}
};

int n, m, q;
matrix pot[LOG];
matrix M, R, G;

void print(matrix a){
	for(int i = 0; i < a.n; i++){
		for(int j = 0; j < a.m; j++){
			cerr << a.M[i][j] << " ";
		}
		cerr << endl;
	}
}

void init(){
	for(int i = 0; i < LOG; i++) pot[i].set(n, n);
	pot[0] = G;
	for(int l = 1; l < LOG; l++){
		pot[l] = pot[l-1] * pot[l-1];
	}
}

int main(){
	ri3(n, m, q);
	G.set(n, n);
	R.set(n, n);
	for(int i = 0; i < m; i++){
		int a, b;
		ri2(a, b);
		a -= 1;
		b -= 1;
		G.M[a][b] += 1;
	}
	init();
	matrix v;
	int s, t, k;
	while(q--){
		ri3(s, t, k);
		R.identity();
		s -= 1;
		t -= 1;
		v.set(n, 1);
		v.M[t][0] = 1;
		for(int i = LOG - 1; i >= 0; i--){
			if(k & (1<<i)){
				v = pot[i] * v;
			}
		}
		printf("%d\n", v.M[s][0]);
	}
	return 0;
}
