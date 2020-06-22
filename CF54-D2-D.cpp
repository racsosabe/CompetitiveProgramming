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

const int N = 100+5;
const int E = 30;

int L;
int len;
int n, k;
int pi[N];
char s[N];
char pat[N];
int go[N][E];
bool vis[N][N];
bool memo[N][N];
int choice[N][N];

int getGo(int u, int c){
	if(go[u][c] != -1) return go[u][c];
	if(s[u] == c + 'a') return go[u][c] = u+1;
	if(u == 0) return go[u][c] = 0;
	return go[u][c] = getGo(pi[u - 1], c);
}

bool DP(int pos, int state){
	if(pos == -1) return true;
	if(vis[pos][state]) return memo[pos][state];
	bool ans = false;
	for(int i=0; i<k; i++){
		int nstate = getGo(state, i);
		if(pos < len){
			if(pat[pos] == '1' and nstate != L) continue;
			if(pat[pos] == '0' and nstate == L) continue;
		}
		if(DP(pos - 1, nstate)){
			ans = true;
			choice[pos][state] = i;
		}
	}
	vis[pos][state] = true;
	return memo[pos][state] = ans;
}

int main(){
	ri2(n, k);
	memset(go, -1, sizeof go);
	scanf("%s",s);
	L = strlen(s);
	reverse(s, s + L);
	int val = 0;
	for(int i=1; i < L; i++){
		while(val > 0 and s[i] != s[val]) val = pi[val-1];
		if(s[val] == s[i]) val++;
		pi[i] = val;
	}
	scanf("%s",pat);
	len = strlen(pat);
	if(DP(n - 1, 0)){
		stack<char> S;
		int state = 0;
		for(int i = n-1; i >= 0; i--){
			S.emplace(choice[i][state] + 'a');
			state = getGo(state, choice[i][state]);
		}
		while(!S.empty()){
			putchar(S.top());
			S.pop();
		}
		puts("");
	}
	else puts("No solution");
	return 0;
}
