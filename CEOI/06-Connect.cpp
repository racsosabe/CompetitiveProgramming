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

	- DP Broken Profile problem.

	- Reduce the problem to a Broken Profile, in which we will take as a parameter

	  the current state of the border of the already processed part of the matrix

	  (0 for an empty or blocked cell and 1 for a dot).

	  Design the only possible configurations according to what we will put in

	  the current cell (If it's blank, a dot or an X) and those will be our possible

	  transitions.

	- Since the number of rows is at most 12, we will just need to carry 13 bits

	  in out border state mask.

	- After that, it reduces to implementation of the DP with reconstruction of the

	  optimal answer.

	- Complexity: O(nm 2^((n + 1) / 2))
*/

const int N = 15 + 5;
const int M = 40 + 5;
const int MASK = 1<<13;
const int inf = 1e9;

int n;
int m;
int total;
vector<int> dot[2];
int memo[N][M][MASK];
bool vis[N][M][MASK];
char s[2 * N][2 * M];
int choice[N][M][MASK];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0 , -1};
int withX[] = {1, 2, 4, 8};

int DP(int i, int j, int mask){
	if(2 * j  == m - 1) return 0;
	if(vis[i][j][mask]) return memo[i][j][mask];
	int x = 2 * i + 1;
	int y = 2 * j + 1;
	int ans = inf;
	int up = (mask >> i) & 1;
	int left = (mask >> (i + 1)) & 1;
	if(s[x][y] == 'X'){
		for(int p = 0; p < 4; p++){
			int nxt = withX[p];
			int U = (nxt >> 2) & 1;
			int L = (nxt >> 3) & 1;
			bool valid = !(up ^ U) and !(left ^ L);
			for(int j = 0; j < 4; j++){
				int vx = x + dx[j];
				int vy = y + dy[j];
				if((nxt >> j) & 1 and (s[vx][vy] != ' ')) valid = false;
			}
			if(not valid) continue;
			int nxtx = 2 * (i + 1) < n? i + 1 : 0;
			int nxty = 2 * (i + 1) < n? j : j + 1;
			int nup = (nxt >> 1) & 1;
			int nleft = (nxt >> 0) & 1;
			int nmask = mask ^ (up << i) ^ (left << (i + 1));
			if(nxtx == i + 1){
				nmask ^= (nup << i) ^ (nleft << (i + 1));
			}
			else{
				nmask ^= (nup << i);
				nmask <<= 1;
				nmask &= total - 1;
			}
			int cand = (int)__builtin_popcount(nxt & 3) + DP(nxtx, nxty, nmask);
			if(ans > cand){
				ans = cand;
				choice[i][j][mask] = nxt;
			}
		}
	}
	else{
		for(int extra = 0; extra < 2; extra++){
			for(int p = 0; p < dot[extra].size(); p++){
				int nxt = dot[extra][p];
				int U = (nxt >> 2) & 1;
				int L = (nxt >> 3) & 1;
				bool valid = !(up ^ U) and !(left ^ L);
				for(int j = 0; j < 4; j++){
					int vx = x + dx[j];
					int vy = y + dy[j];
					if((nxt >> j) & 1 and (s[vx][vy] != ' ')) valid = false;
				}
				if(not valid) continue;
				int nxtx = 2 * (i + 1) < n? i + 1 : 0;
				int nxty = 2 * (i + 1) < n? j : j + 1;
				int nup = (nxt >> 1) & 1;
				int nleft = (nxt >> 0) & 1;
				int nmask = mask ^ (up << i) ^ (left << (i + 1));
				if(nxtx == i + 1){
					nmask ^= (nup << i) ^ (nleft << (i + 1));
				}
				else{
					nmask ^= (nup << i);
					nmask <<= 1;
					nmask &= total - 1;
				}
				int cand = __builtin_popcount(nxt & 3) + extra + DP(nxtx, nxty, nmask);
				if(ans > cand){
					ans = cand;
					choice[i][j][mask] = nxt;
				}
			}
		}
	}
	vis[i][j][mask] = true;
	return memo[i][j][mask] = ans;
}

int solve(){
	return DP(0, 0, 0);
}

void build(int i, int j, int mask){
	if(2 * j == m - 1) return;
	int nxt = choice[i][j][mask];
	int x = 2 * i + 1;
	int y = 2 * j + 1;
	if(nxt and s[x][y] != 'X') s[x][y] = '.';
	for(int k = 0; k < 4; k++){
		int vx = x + dx[k];
		int vy = y + dy[k];
		if(nxt & (1<<k)){
			s[vx][vy] = '.';
		}
	}
	int nxtx = 2 * (i + 1) < n? i + 1 : 0;
	int nxty = 2 * (i + 1) < n? j : j + 1;
	int up = (mask >> i) & 1;
	int left = (mask >> (i + 1)) & 1;
	int nup = (nxt >> 1) & 1;
	int nleft = (nxt >> 0) & 1;
	int nmask = mask ^ (up << i) ^ (left << (i + 1));
	if(nxtx == i + 1){
		nmask ^= (nup << i) ^ (nleft << (i + 1));
	}
	else{
		nmask ^= (nup << i);
		nmask <<= 1;
		nmask &= total - 1;
	}
	build(nxtx, nxty, nmask);
}

int main(){
	ri2(n, m);
	getchar();
	int X = 0;
	total = 1 << ((n - 1) / 2 + 1);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			s[i][j] = getchar();
			if(s[i][j] == 'X') X += 1;
		}
		getchar();
	}
	dot[0].emplace_back(0);
	for(int i = 0; i < 4; i++){
		int j = add(i, 1, 4);
		dot[1].emplace_back((1<<i) | (1<<j));
		j = add(i, 2, 4);
		dot[1].emplace_back((1<<i) | (1<<j));
	}
	int ans = solve();
	printf("%d\n", ans + X / 2);
	build(0, 0, 0);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			putchar(s[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
