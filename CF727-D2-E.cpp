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
const long long MOD = 1000000000 + 99999;

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

int add(int a, int b, int m = MOD){
	return a + b < m? a + b : a + b - m;
}

int mul(ll a, ll b, int m = MOD){
	return (a * b) % m;
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

const int N = 2000000+5;
const int B[] = {311, 257};

int n;
int k;
int g;
int q;
int len;
char s[N];
int h[3][N];
int pot[3][N];
int poti[3][N];

void init(){
	for(int id = 0; id < 2; id++){
		pot[id][0] = 1;
		for(int i=1; i<N; i++){
			pot[id][i] = mul(pot[id][i-1], B[id]);
		}
		poti[id][N-1] = pow_mod(pot[id][N-1], MOD-2);
		for(int i=N-2; i>=0; i--){
			poti[id][i] = mul(poti[id][i+1], B[id]);
		}
		for(int i=1; i<=len + len; i++){
			int x = s[(i - 1) % len] - 'a' + 1;
			h[id][i] = add(h[id][i-1], mul(pot[id][i], x));
		}
	}
}

ii getHash(string &s){
	vector<int> v;
	for(int id=0; id<2; id++){
		int hsh = 0;
		for(int i=0; i < s.size(); i++){
			hsh = add(hsh, mul(s[i] - 'a' + 1, pot[id][i]));
		}
		v.emplace_back(hsh);
	}
	return mp(v[0], v[1]);
}

ii getSubhash(int L, int R){
	vector<int> v;
	for(int id = 0; id < 2; id++){
		int hsh = mul(add(h[id][R + 1], MOD - h[id][L]), poti[id][L+1]);
		v.emplace_back(hsh);
	}
	return mp(v[0], v[1]);
}

int main(){
	ri2(n, k);
	scanf("%s",s);
	len = n * k;
	init();
	ri(q);
	map<ii, int> pos;
	string pat;
	for(int i=1; i<=q; i++){
		cin >> pat;
		ii H = getHash(pat);
		pos[H] = i;
	}
	vector<bool> used(q + 1, false);
	vector<int> ans;
	for(int start=0; start<k; start++){
		for(int i=0; i<n; i++){
			int L = start + k * i;
			int R = L + k - 1;
			ii cur = getSubhash(L, R);
			if(pos.count(cur)){
				int id = pos[cur];
				if(used[id]) break;
				else{
					ans.emplace_back(id);
					used[id] = true;
				}
			}
			else break;
		}
		if(ans.size() < n){
			for(auto x : ans) used[x] = false;
		}
		else break;
		ans.clear();
	}
	if(ans.empty()) puts("NO");
	else{
		puts("YES");
		for(int i=0; i<ans.size(); i++){
			printf("%d%c",ans[i]," \n"[i + 1 == ans.size()]);
		}
	}
	return 0;
}
