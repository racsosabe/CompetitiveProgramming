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

		- Interesting Graph problem.

		- The approach is just count the number

		  of lifts are going to be needed for each

		  book.

		- Immediate answers: a == b, then we have 0,

		  else, if there are no gaps, it's impossible

		  to reach state b.

		- Then, the transitions needed among books

		  that connect different rows can form a cycle

		  of transitions. The ones that are meant to

		  be put in the same row will be handled now.

		- For the books that go in the same row, we will

		  get the LIS of their final positions, since

		  we can virtually correctly put then without lifts.

		  So, the other ones will be added as obligatory lifts.

		  Special case: when the original row state is a 
		  
		  permutation of the final row state, in this case we add

		  one extra lift for pivot.

		- If all the rows in the transition cycle are

		  completely filled, then a pivot movement will

		  be needed, so they add one to the number of extra

		  lifts, else one gap of them can be used as pivot

		  so we don't add anything.

		- Complexity: O(nlogm)

*/

const int N = 1000+5;
const int K = 1000000+5;

vi G[N];
bool vis[N];
int n, m, k;
int a[N][N];
int b[N][N];
int books[N];
int xa[K], xb[K];
int ya[K], yb[K];
vii correctRow[N];

int getBestFit(int row){
	int len = 0;
	vi LIS;
	sort(all(correctRow[row]));
	for(int i=0; i<correctRow[row].size(); i++){
		int x = correctRow[row][i].second;
		if(LIS.size() == 0 or LIS.back() < x){
			LIS.pb(x);
			len++;
		}
		else{
			int lo = 0, hi = len-1;
			while(lo < hi){
				int mi = lo + (hi-lo)/2;
				if(LIS[mi] < x) lo = mi+1;
				else hi = mi;
			}
			LIS[lo] = x;
		}
	}
	if(len == correctRow[row].size()) return 0;
	int ans = 0;
	if(correctRow[row].size() == m) ans++; // Need a gap to solve it
	ans += correctRow[row].size() - len; // Will need to be lifted
	return ans;
}

int DFS(int u){
	int ans = (books[u] == m);
	vis[u] = true;
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(!vis[v]){
			ans &= DFS(v);
		}
	}
	return ans;
}

int solve(){
	bool equal = true;
	bool gap = false;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j] == 0) gap = true;
			if(a[i][j] != b[i][j]) equal = false;
			if(a[i][j] > 0) books[i]++;
			xa[a[i][j]] = i;
			ya[a[i][j]] = j;
			xb[b[i][j]] = i;
			yb[b[i][j]] = j;
		}
	}
	if(equal) return 0;
	if(!gap) return -1;
	int ans = 0;
	for(int book = 1; book <= k; book++){
		if(xa[book] == xb[book]){
			correctRow[xa[book]].pb(mp(ya[book],yb[book]));
		}
		else{
			G[xa[book]].pb(xb[book]);
			G[xb[book]].pb(xa[book]);
			ans++; // An obligatory exchange
		}
	}
	for(int i=0; i<n; i++){
		ans += getBestFit(i);
	}
	for(int i=0; i<n; i++){
		if(!vis[i] and G[i].size()){
			ans += DFS(i);
		}
	}
	return ans;
}

int main(){
	ri2(n,m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			ri(a[i][j]);
			k = max(k,a[i][j]);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			ri(b[i][j]);
		}
	}
	cout << solve() << endl;
	return 0;
}
