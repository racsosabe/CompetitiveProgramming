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
		- Simple Greedy + TopoSort problem

		- Just build the graph of dependencies with (u,v) iff u must be known
		  before v.

		- Then, iterate over all the m bits of the possible answers and get the

		  number of 1s that would be generated if we replace the current bit

		  by 0 or 1.

		- Greedily assign the bit values accordingly.

		- Complexity: O(nm)

*/

const int N = 5000+5;

int n, m;
int ans1[N];
int ans2[N];
string v[N];
bool vis[N];
int carry[N];
stack<int> S;
vector<int> G[N];
vector<int> D[N];
int operation[N];
int TopoOrder[N];
map<string,int> id;

void DFS(int u){
	vis[u] = true;
	for(int v:G[u]){
		if(vis[v]) continue;
		DFS(v);
	}
	S.emplace(u);
}

void TopoSort(){
	for(int i=1; i<=n; i++){
		if(vis[i]) continue;
		DFS(i);
	}
	int pos = 0;
	while(!S.empty()){
		TopoOrder[pos++] = S.top();
		S.pop();
	}
}

int solve(int pos, int bit){
	for(int i=0; i<=n; i++){
		carry[i] = 0;
	}
	carry[0] = bit;
	int ones = 0;
	for(int i=0; i<n; i++){
		int u = TopoOrder[i];
		if(operation[u] == 0){
			if(v[u][pos] == '1'){
				carry[u] = 1;
			}
			else carry[u] = 0;
		}
		else{
			int a = D[u][0];
			int b = D[u][1];
			if(operation[u] == 1){
				carry[u] = (carry[a] & carry[b]);
			}
			else if(operation[u] == 2){
				carry[u] = (carry[a] | carry[b]);
			}
			else{
				carry[u] = (carry[a] ^ carry[b]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		ones += carry[i];
	}
	return ones;
}

int main(){
	ri2(n,m);
	string s;
	id["?"] = 0;
	for(int i=1; i<=n; i++){
		cin >> s;
		id[s] = i;
		cin >> s;
		cin >> s;
		if(isdigit(s[0])){
			v[i] = s;
			continue;
		}
		int u = id[s];
		if(u > 0){
			G[u].emplace_back(i);
		}
		D[i].emplace_back(u);
		cin >> s;
		if(s[0] == 'A') operation[i] = 1;
		else if(s[0] == 'O') operation[i] = 2;
		else operation[i] = 3;
		cin >> s;
		u = id[s];
		if(u > 0){
			G[u].emplace_back(i);
		}
		D[i].emplace_back(u);
	}
	TopoSort();
	for(int i=0; i<m; i++){
		int cand0 = solve(i,0);
		int cand1 = solve(i,1);
		if(cand0 == cand1){
			ans1[i] = ans2[i] = 0;
		}
		else{
			if(cand0 < cand1){
				ans1[i] = 0;
				ans2[i] = 1;
			}
			else{
				ans1[i] = 1;
				ans2[i] = 0;
			}
		}
	}
	for(int i=0; i<m; i++){
		putchar('0' + ans1[i]);
	}
	puts("");
	for(int i=0; i<m; i++){
		putchar('0' + ans2[i]);
	}
	puts("");
	return 0;
}
