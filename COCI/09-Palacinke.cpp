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
const int MOD = 5557;

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

int mul(int a, int b, int m = MOD){
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

/*
	Author: Racso Galvan

	Idea:

	- Matrix Exponentiation and IEP problem.

	- Just write a simple recursive function to compute the number of ways to 

	  get to a node v using T seconds given a graph.

	- It's easy to notice that we would need a square matrix of size 2 * n to

	  be able to compute the value of all nodes simultaneously.

	- Now, we can use Inclusion-Exclusion Principle to ban some set of ingredients

	  and compute the number of ways to get to node 1 without going into the

	  shop of any edge that contains at least one of them, the final sum is 

	  computed as the Principle states.

	- Complexity: O(n^3 * 2^b * logT), where b is the number of ingredients.

*/

const int N = 25 * 16 + 2;
const string ingredients = "BJMP";

struct matrix{
	int n;
	int m;
	vector<vi> M;
	matrix(){}

	matrix(int n, int m) : n(n), m(m), M(n, vi(m, 0)){}

	matrix(vector<vi> v){
		assert(!v.empty());
		assert(!v[0].empty());
		M = v;
		n = M.size();
		m = M[0].size();
	}

	void set(int _n, int _m){
		n = _n;
		m = _m;
		M = vector<vi>(n, vi(m, 0));
	}

	void identity(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				M[i][j] = i == j;
			}
		}
	}

	matrix operator * (matrix b) {
		matrix res(n, b.m);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < b.m; j++){
				for(int k = 0; k < m; k++){
					res.M[i][j] = add(res.M[i][j], mul(M[i][k], b.M[k][j]));
				}
			}
		}
		return res;
	}

	matrix operator + (matrix b){
		matrix res = b;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				res.M[i][j] = add(res.M[i][j], M[i][j]);
			}
		}
		return res;
	}

	void operator *= (matrix b){
		vector<vi> C(n, vi(b.m, 0));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < b.m; j++){
				for(int k = 0; k < m; k++){
					C[i][j] = add(C[i][j], mul(M[i][k], b.M[k][j]));
				}
			}
		}
		M = C;
		n = M.size();
		m = M[0].size();
	}

	void operator += (matrix b){
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

	void print(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				cerr << M[i][j] << " ";
			}
			cerr << endl;
		}
	}
};

int n;
int m;
int T;
int len;
vii G[N];
matrix f;
matrix M;

int ord(char c){
	for(int i = 0; i < (int)ingredients.size(); i++){
		if(c == ingredients[i]) return i;
	}
	return -1;
}

int getNode(int node, int minus){
	return node * 2 + minus;
}

void buildMatrix(int mask){
	len = n * 2;
	M.set(len, len);
	for(int i = 0; i < n; i++){
		int u = i;
		for(auto e : G[i]){
			int v = e.second;
			if(mask & e.first) continue;
			int col = len / 2 + u;
			int row = v;
			M.M[row][col] += 1;
		}
		for(auto e : G[i]){
			int v = e.second;
			int col = u;
			int row = v;
			M.M[row][col] += 1;
		}
	}
	for(int i = len / 2; i < len; i++){
		M.M[i][i - len / 2] = 1;
	}
	f.set(len, 1);
	for(auto e : G[0]){
		int v = e.second;
		int row = v;
		f.M[row][0] += 1;
	}
	f.M[len / 2][0] = 1;
}

matrix fastexpo(int b){
	matrix res(len, len);
	matrix cur(len, len);
	cur.identity();
	matrix pot(len, len);
	pot = M;
	matrix cur_pot(len, len);
	cur_pot = M;
	while(b > 0){
		if(b & 1){
			res += cur * cur_pot;
			cur_pot *= pot;
		}
		cur += pot * cur;
		pot *= pot;
		b >>= 1;
	}
	return res;
}

int main(){
	ri2(n, m);
	char s[5];
	for(int i = 0; i < m; i++){
		int u, v;
		ri2(u, v);
		u--; v--;
		scanf("%s", s);
		int mask = 0;
		for(int i = 0; s[i]; i++){
			mask |= 1<<ord(s[i]);
		}
		G[u].emplace_back(mp(mask, v));
	}
	ri(T);
	int ans = 0;
	for(int mask = 0; mask < 16; mask++){
		buildMatrix(mask);
		matrix B = fastexpo(T - 1);
		matrix res = B * f + f;
		int sgn = __builtin_popcount(mask) & 1? MOD - 1 : 1;
		ans = add(ans, mul(sgn, res.M[0][0]));
	}
	printf("%d\n", ans);
	return 0;
}
