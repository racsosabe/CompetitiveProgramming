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

const int N = 10;
const int n = 8;

int done;
char s[N][N];
char ans[N][N];
vector<int> res;

bool check(vector<int> &v){
	int included = 0;
	for(int i = 0; i < n; i++){
		int x = i;
		int y = v[i];
		if(s[x][y] == 'Q') included += 1;
	}
	return included == done;
}

void backtracking(int pos, vector<int> &v){
	if(pos == n){
		if(check(v)) res = v;
		return;
	}
	for(int i = 0; i < n; i++){
		bool valid = true;
		for(int j = 0; j < pos; j++){
			int dx = abs(j - pos);
			int dy = abs(v[j] - i);
			if(dx == dy or !dx or !dy){
				valid = false;
			}
		}
		if(not valid) continue;
		v.emplace_back(i);
		backtracking(pos + 1, v);
		v.pop_back();
	}
}

void update(){
	memset(ans, '.', sizeof ans);
	for(int i = 0; i < n; i++){
		ans[i][res[i]] = 'Q';
		ans[i][n] = '\0';
	}
}

int main(){
	for(int i = 0; i < n; i++){
		scanf("%s", s[i]);
		for(int j = 0; j < n; j++){
			if(s[i][j] == 'Q') done += 1;
		}
	}
	vector<int> v;
	backtracking(0, v);
	if(res.empty()) puts("No Answer");
	else{
		update();
		for(int i = 0; i < n; i++){
			printf("%s\n", ans[i]);
		}
	}
	return 0;
}
