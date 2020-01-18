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

const int N = 200+5;

int n;
bool G[N][N];
int party[N];

void solve(vi a){
	int odd_neigh = -1;
	vector<int> neighbors;
	for(int i=0; i<a.size(); i++){
		int u = a[i];
		neighbors.clear();
		for(int j=0; j<a.size(); j++){
			int v = a[j];
			if(G[u][v]) neighbors.emplace_back(v);
		}
		if(neighbors.size() & 1){
			odd_neigh = u;
			break;
		}
	}
	if(odd_neigh == -1) return;
	vector<int> newA;
	for(int i=0; i<a.size(); i++){
		if(a[i] == odd_neigh) continue;
		newA.emplace_back(a[i]);
	}
	for(auto x : neighbors){
		for(auto y : neighbors){
			if(x == y) continue;
			G[x][y] = !G[x][y];
		}
	}
	solve(newA);
	int toParty = 0;
	for(auto x : neighbors){
		if(party[x]) toParty++;
	}
	party[odd_neigh] = (toParty % 2 == 0);
}

int main(){
	ri(n);
	int q, x;
	for(int i=1; i<=n; i++){
		ri(q);
		for(int j=0; j<q; j++){
			ri(x);
			G[i][x] = true;
		}
	}
	vi v;
	for(int i=1; i<=n; i++){
		v.emplace_back(i);
	}
	solve(v);
	vi ans;
	for(int i=1; i<=n; i++){
		if(party[i]) ans.emplace_back(i);
	}
	cout << ans.size() << endl;
	for(int i=0; i<ans.size(); i++){
		printf("%d%c",ans[i]," \n"[i + 1 == ans.size()]);
	}
	return 0;
}
