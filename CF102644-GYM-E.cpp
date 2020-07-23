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
	int n;
	unsigned int M[65][65];
	node(bool identity = false){
		n = 64;
		memset(M, 0, sizeof M);
		if(identity){
			for(int i = 0; i < n; i++) M[i][i] = 1;
		}
	}

	node operator * (node b){
		node q;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				q.M[i][j] = 0;
				for(int k = 0; k < n; k++){
					q.M[i][j] += M[i][k] * b.M[k][j];
				}
			}
		}
		return q;
	}

	node operator + (node b){
		node q;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				q.M[i][j] = M[i][j] + b.M[i][j];
			}
		}
		return q;
	}

	void operator *= (node b){
		node q;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				q.M[i][j] = 0;
				for(int k = 0; k < n; k++){
					q.M[i][j] += M[i][k] * b.M[k][j];
				}
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				M[i][j] = q.M[i][j];
			}
		}

	}

	void operator += (node b){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				M[i][j] += b.M[i][j];
			}
		}
	}

	void operator = (node b){	
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				M[i][j] = b.M[i][j];
			}
		}
	}
};

int k;
int n = 64;
int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
node G;
node I(true);

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < 8 and j < 8;
}

void build(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int u = i * 8 + j;
			for(int k = 0; k < 8; k++){
				int vx = i + dx[k];
				int vy = j + dy[k];
				if(!validPos(vx, vy)) continue;
				int v = vx * 8 + vy;
				G.M[u][v] += 1;
			}
		}
	}
}

node fastexpo(int b){
	node res;
	node sum = I;
	node pot = G;
	node cur = G;
	while(b > 0){
		if(b & 1){
			res += sum * cur;
			cur *= pot;
		}
		sum += sum * pot;
		pot *= pot;
		b >>= 1;
	}
	return res;
}

int main(){
	ri(k);
	build();
	node res = fastexpo(k) + I;
	unsigned int ans = 0;
	for(int i = 0; i < n; i++){
		ans += res.M[0][i];
	}
	printf("%u\n", ans);
	return 0;
}
