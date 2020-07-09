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

	- 0-1 BFS problem.

	- This problem gives TLE if we use Dijkstra's Algorithm.

	- Notice that since the red-light time isn't important for our moves, we can

	  just store the time left for the next change (green to red) for each node.

	  So we will use nodes as pairs (pos, left).

	- Also, if we have ended in (m - 1, X) with k color changes, then the total time

	  elapsed is k * (r + g) + (g - X).

	- We can go from pos to pos + 1 or pos - 1 (let it be nxt) if the distance doesn't exceed 

	  left. In that case, we can handle two situations:

	  1) left > distance: We go to (nxt, left - distance) with 0 color changes.

	  2) left = distance: We go to (nxt, g) with 1 color change.

	- Now, since we only have edges with weights 0 and 1 we can use 0-1 BFS to 
	  
	  achieve a nice complexity.

	- Complexity: O(mg)

*/

const int N = 10000+5;
const int M = 1000+5;
const int inf = 1<<29;

int n;
int m;
int d[N];
int g, r;
int dis[N];
int D[N][M];

void BFS(){
	for(int i=0; i<m; i++){
		for(int j=0; j<=g; j++){
			D[i][j] = inf;
		}
	}
	D[0][g] = 0;
	deque<ii> Q;
	Q.emplace_front(mp(0, g));
	while(!Q.empty()){
		int u = Q.front().first;
		int t = Q.front().second;
		Q.pop_front();
		if(u > 0 and dis[u-1] <= t){
			int sum = 0;
			int nxt = t - dis[u-1];
			int v = u - 1;
			if(nxt == 0 and v != m-1){
				nxt = g;
				sum += 1;
			}
			if(D[v][nxt] > D[u][t] + sum){
				D[v][nxt] = D[u][t] + sum;
				if(sum == 0) Q.emplace_front(mp(v, nxt));
				else Q.emplace_back(mp(v, nxt));
			}
		}
		if(u + 1 < m and dis[u] <= t){
			int sum = 0;
			int nxt = t - dis[u];
			int v = u + 1;
			if(nxt == 0 and v != m-1){
				nxt = g;
				sum += 1;
			}
			if(D[v][nxt] > D[u][t] + sum){
				D[v][nxt] = D[u][t] + sum;
				if(sum == 0) Q.emplace_front(mp(v, nxt));
				else Q.emplace_back(mp(v, nxt));
			}
		}
	}
}

int main(){
	ri2(n, m);
	for(int i=0; i<m; i++) ri(d[i]);
	ri2(g, r);
	sort(d, d + m);
	for(int i=0; i+1<m; i++){
		dis[i] = abs(d[i] - d[i+1]);
	}
	BFS();
	int ans = -1;
	for(int i=0; i<=g; i++){
		if(D[m-1][i] < inf){
			if(ans == -1 or ans > D[m-1][i] * (r + g) + g - i){
				ans = D[m-1][i] * (r + g) + g - i;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
