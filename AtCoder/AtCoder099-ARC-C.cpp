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

		- Classical Graph & DP problem.

		- Reduce the problem to split a graph G in two cliques such that the sum

		  of edges in each clique is minimum.

		- Observation 1: if Complement(G) is bipartite then G can be splitted
		 
	       	  in two cliques.

		- Observation 2: if Complement(G) is bipartite then it can be decomposed
	       
		  into bipartite components.

		- Final observation: We can use DP to get the possible values of the

		  size of the first subset using a knapsack-style DP and iterate

		  over the values and minimize.

		- Complexity: O(n + M), where M is the number of edges in the complement
		  of G.

*/

const int N = 700+5;

vi G[N];
int n, m;
int C[N];
vii comps;
int M[N][N];
bool memo[N][N];

bool bipartite(){
	for(int i=1; i<=n; i++){
		if(C[i] == -1){
			queue<int> Q;
			C[i] = 0;
			Q.emplace(i);
			int c1 = 1;
			int c2 = 0;
			while(!Q.empty()){
				int u = Q.front(); Q.pop();
				for(int i=0; i<G[u].size(); i++){
					int v = G[u][i];
					if(C[v] == -1){
						C[v] = 1^C[u];
						if(C[v] == 0) c1++;
						else c2++;
						Q.emplace(v);
					}
					else if(C[v] == C[u]) return false;
				}
			}
			comps.emplace_back(mp(c1,c2));
		}
	}
	return true;
}

int getValue(int a, int b){
	int ans = a * (a-1) + b * (b-1);
	ans >>= 1;
	return ans;
}

int main(){
	ri2(n,m);
	for(int i=1; i<=n; i++){
		C[i] = -1;
		for(int j=i+1; j<=n; j++){
			M[i][j] = M[j][i] = 1;
		}
	}
	int a, b;
	for(int i=0; i<m; i++){
		ri2(a,b);
		M[a][b] = M[b][a] = 0;
	}
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			if(M[i][j]){
				G[i].emplace_back(j);
				G[j].emplace_back(i);
			}
		}
	}
	int ans;
	if(!bipartite()) ans = -1;
	else{
		memo[0][0] = true;
		for(int i=1; i<=comps.size(); i++){
			for(int val=0; val <= n; val++){
				if(val >= comps[i-1].first){
					if(memo[i-1][val - comps[i-1].first]) memo[i][val] = true;
				}
				if(val >= comps[i-1].second){
					if(memo[i-1][val - comps[i-1].second]) memo[i][val] = true;
				}
			}
		}
		ans = INT_MAX;
		for(int i=0; i<=n; i++){
			if(memo[comps.size()][i]){
				ans = min(ans,getValue(i,n-i));
			}
		}
	}
	cout << ans << endl;
	return 0;
}
