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

		- Nice DP Memory Optimized problem
		
		- Since our ML is just 32M, we need to be careful with our
		 
		  memoization tables' size.

		- First of all, we can just simulate the decision tree of the

		  problem by setting which subsquare is white or black and then

		  make the recursion to the other two.

		  It's easy to see that this Recursion will have at most O(logn)

		  depth so we can handle it easily in time by doing the naive idea.

		- Now, about the memory, we need to notice that if we do a bottom-up DP

		  and simulate the painting of subsquares of optimal decisions, then

		  the final one will be the square needed, so we can save memory

		  by using only 2 tables of memo for the answer and the original 

		  p table to make the changes if needed.

		- Complexity: O(n^2 logn) time and O(n^2) memory.
*/

const int N = 512;
const int LOG = 10;

int n;
int p[N][N];
int ac[N][N];
int memo[N][N][3];
int dx[] = {0,0,1,1};
int dy[] = {0,1,0,1};

int query(int x, int y, int d){
	int L = 1<<d;
	int vx = x + L - 1;
	int vy = y + L - 1;
	int ans = ac[vx][vy];
	if(x > 0) ans -= ac[x-1][vy];
	if(y > 0) ans -= ac[vx][y-1];
	if(x > 0 and y > 0) ans += ac[x-1][y-1];
	return ans;
}

void Fill(int x, int y, int L, int val){
	for(int i=x; i<x+L; i++){
		for(int j=y; j<y+L; j++){
			p[i][j] = val;
		}
	}
}

void solve(){
	for(int d=1; 1<<d <= n; d++){
		int pos = d&1;
		int last = 1^pos;
		int L = 1<<d;
		int l = 1<<(d-1);
		for(int i=0; i<n; i+=L){
			for(int j=0; j<n; j+=L){
				vi perm(4,0);
				int ans = INT_MAX;
				int white = -1;
				int black = -1;
				for(int k=0; k<4; k++) perm[k] = k;
				do{
					int act = 0;
					for(int p=0; p<4; p++){
						int vx = i + dx[perm[p]]*l;
						int vy = j + dy[perm[p]]*l;
						if(p == 0){
							act += query(vx,vy,d-1);
						}
						else if(p == 1){
							act += l*l - query(vx,vy,d-1);
						}
						else{
							act += memo[vx][vy][last];
						}
					}
					if(act < ans){
						ans = act;
						white = perm[0];
						black = perm[1];
					}
				}while(next_permutation(all(perm)));
				int vx = i + dx[white]*l;
				int vy = j + dy[white]*l;
				Fill(vx,vy,l,0);
				vx = i + dx[black]*l;
				vy = j + dy[black]*l;
				Fill(vx,vy,l,1);
				memo[i][j][pos] = ans;
			}
		}
	}
}

int main(){
	ri(n);
	int d = 31-__builtin_clz(n);
	getchar();
	char c;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			c = getchar();
			ac[i][j] = c - '0';
			p[i][j] = ac[i][j];
			memo[i][j][0] = 0;
		}
		getchar();
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i > 0) ac[i][j] += ac[i-1][j];
			if(j > 0) ac[i][j] += ac[i][j-1];
			if(i > 0 and j > 0) ac[i][j] -= ac[i-1][j-1];
		}
	}
	solve();
	int ans = memo[0][0][d&1];
	cout << ans << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%d",p[i][j]);
		}
		puts("");
	}
	return 0;
}
