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
	Author: Racso Galvan

	Idea: 
		- Very nice Graphs problem.

		- First, use the transformation proposed by the official editorial,

		  which is the following:

		  (u, v, #) -> (nu, v, c) iff exists edge (u, nu) and it has label c

		  (u, v, c) -> (u, nv, #) iff exists edge (nv, v) and it has label c

		  Then, it all turns out to be a multisource BFS for preprocessing

		  the distances and get the optimal path for each query.

		- Complexity: O(d * (n^2 + |E|) + nm), where E is the alphabet used.
*/

const int N = 400+5;
const int M = 100+5;
const int E = 27;

int n, m;
int a[M];
int D[N][N][E];
int py[N][N][E];
int px[N][N][E];
char pc[N][N][E];
vector<int> W[N];
vector<int> Gt[N][E];
vector<int> G[N];

void init(){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int c = 0; c < E; c++){
				D[i][j][c] = -1;
				px[i][j][c] = -1;
				py[i][j][c] = -1;
				pc[i][j][c] = -1;
			}
		}
		D[i][i][0] = 0;
	}
	for(int i=1; i<=n; i++){
		for(int c = 0; c < E; c++){
			for(int k=0; k<Gt[i][c].size(); k++){
				int vx = Gt[i][c][k];
				int vy = i;
				int vc = 0;
				if(D[vx][vy][vc] == -1){
					D[vx][vy][vc] = 1;
					px[vx][vy][vc] = i;
					py[vx][vy][vc] = i;
					pc[vx][vy][vc] = c - 1 + 'a';
				}
			}
		}
	}
}

void BFS(){
	queue<int> Q;
	for(int d = 0; d < 2; d++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				for(int c = 0; c < E; c++){
					if(D[i][j][c] == d){
						Q.emplace(i);
						Q.emplace(j);
						Q.emplace(c);
					}
				}
			}
		}
	}
	while(!Q.empty()){
		int ux = Q.front(); Q.pop();
		int uy = Q.front(); Q.pop();
		int uc = Q.front(); Q.pop();
		if(uc == 0){
			for(int i=0; i<G[uy].size(); i++){
				int vx = ux;
				int vy = G[uy][i];
				int vc = W[uy][i];
				if(D[vx][vy][vc] == -1){
					D[vx][vy][vc] = D[ux][uy][uc] + 1;
					px[vx][vy][vc] = ux;
					py[vx][vy][vc] = uy;
					pc[vx][vy][vc] = vc - 1 + 'a';
					Q.emplace(vx);
					Q.emplace(vy);
					Q.emplace(vc);
				}
			}
		}
		else{
			for(int i=0; i<Gt[ux][uc].size(); i++){
				int vx = Gt[ux][uc][i];
				int vy = uy;
				int vc = 0;
				if(D[vx][vy][vc] == -1){
					D[vx][vy][vc] = D[ux][uy][uc] + 1;
					px[vx][vy][vc] = ux;
					py[vx][vy][vc] = uy;
					pc[vx][vy][vc] = uc - 1 + 'a';
					Q.emplace(vx);
					Q.emplace(vy);
					Q.emplace(vc);
				}
			}
		}
	}
}

void solve(int pos){
	int x = a[pos];
	int y = a[pos+1];
	int ans = D[x][y][0];
	int c = 0;
	if(ans == -1){
		puts("-1");
	}
	else{
		vector<char> s1, s2;
		while(x != y){
			if(c){
				s1.emplace_back(pc[x][y][c]);
			}
			else{
				s2.emplace_back(pc[x][y][c]);
			}
			int tx = px[x][y][c];
			int ty = py[x][y][c];
			int tc = c ? 0 : pc[x][y][c] - 'a' + 1;
			x = tx;
			y = ty;
			c = tc;
		}
		printf("%d ",ans);
		for(int i = 0; i < s1.size(); i++){
			putchar(s1[i]);
		}
		for(int i=s2.size()-1; i >= 0; i--){
			putchar(s2[i]);
		}
		puts("");
	}
}

int main(){
	ri2(n,m);
	int u, v;
	for(int i=0; i<m; i++){
		ri2(u,v);
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		Gt[v][c-'a'+1].emplace_back(u);
		W[u].emplace_back(c - 'a' + 1);
		G[u].emplace_back(v);
	}
	init();
	BFS();
	int d;
	ri(d);
	for(int i=1; i<=d; i++){
		ri(a[i]);
	}
	for(int i=1; i+1 <= d; i++){
		solve(i);
	}
	return 0;
}
