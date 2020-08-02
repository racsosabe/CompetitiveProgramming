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

	- BFS problem.

	- We can just try to assign 0 or 1 to all the output states (except from the
	
	  gates 0 and 1, which have a fixed output state) and then stabilize it by

	  modifying the gates that don't make sense.

	- Then, we propagate the output states to each neighbor and add to a queue

	  all the gates that are invalid to correct them.

	- We use a BFS style algorithm to propagate corrections, by updating a gate

	  and adding all the new invalid neighbor gates.

	- Each gate is modified at most twice according to the editorial idea, so our 
	
	  complexity will be linear.

	- Complexity: O(n + m)

*/

const int N = 10000+5;

int n;
int val[N];
int sumin[N];
vector<int> G[N];
vector<int> possible[N];

int eval(int i){
	if(sumin[i] == 0) return 2;
	return sumin[i] < 0? 0 : 1;
}

bool valid(int i){
	return eval(i) == val[i];
}

void use(int x){
	for(int i = 0; i < n; i++){
		val[i] = x;
		sumin[i] = 0;
	}
	val[0] = 0;
	sumin[0] = -1;
	val[1] = 1;
	sumin[1] = 1;
	for(int i = 0; i < n; i++){
		for(int v : G[i]){
			if(val[i]) sumin[v] += 1;
			else sumin[v] -= 1;
		}
	}
	queue<int> Q;
	for(int i = 0; i < n; i++){
		if(not valid(i)) Q.emplace(i);
	}
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		int cur = val[u];
		int state = eval(u);
		if(cur == state) continue;
		for(int v : G[u]){
			if(cur == 0) sumin[v] += 1;
			else if(cur == 1) sumin[v] -= 1;

			if(state == 0) sumin[v] -= 1;
			else if(state == 1) sumin[v] += 1;

			if(not valid(v)){
				Q.emplace(v);
			}
		}
		val[u] = state;
	}
	for(int i = 0; i < n; i++) possible[i].emplace_back(val[i]);
}

int main(){
	ri(n);
	for(int i = 2; i < n; i++){
		int k;
		ri(k);
		for(int j = 0; j < k; j++){
			int x;
			ri(x);
			G[x].emplace_back(i);
		}
	}
	use(0);
	use(1);
	for(int i = 0; i < n; i++){
		if(possible[i][0] == possible[i][1]){
			if(possible[i][0] == 2) puts("1/2");
			else printf("%d\n", possible[i][0]);
		}
		else puts("?");
	}
	return 0;
}
