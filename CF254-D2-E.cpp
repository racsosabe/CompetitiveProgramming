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

const int N = 400+5;
const int M = 800+5;
const int inf = 1e8;

int n;
int m;
int v;
int F[N];
int a[N];
int memo[N][M];
int nxtJ[N][M];
vector<int> w[N];
int choice[N][M];

void print(int i, int j){
	int use = choice[i][j];
	vector<int> ans;
	for(int k = 0; k < w[i].size(); k++){
		if(use >= F[w[i][k]]){
			ans.emplace_back(w[i][k]);
			use -= F[w[i][k]];
		}
	}
	printf("%d ",(int)ans.size());
	for(int i=0; i<ans.size(); i++){
		printf("%d%c",ans[i]," \n"[i + 1 == ans.size()]);
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ri2(n, v);
	for(int i=1; i<=n; i++){
		ri(a[i]);
	}
	ri(m);
	for(int i=1; i<=m; i++){
		int l, r;
		ri3(l, r, F[i]);
		for(int j = l; j <= r; j++) w[j].emplace_back(i);
	}
	for(int i = n; i >= 1; i--){
		int len = w[i].size();
		sort(all(w[i]), [&] (int i, int j){
			return F[i] < F[j];
		});
		for(int j = 0; j <= 400; j++){
			int todayFood, maxFood;
			if(j >= v){
				maxFood = a[i];
			}
			else{
				maxFood = a[i] + j - v;
			}
			todayFood = max(0, a[i] + j - v);
			memo[i][j] = 0;
			int pos = 0;
			int sum = 0;
			for(int useToday = 0; useToday <= todayFood; useToday++){
				int forTomorrow = min(maxFood, todayFood - useToday);
				while(pos < w[i].size() and sum + F[w[i][pos]] <= useToday){
					sum += F[w[i][pos]];
					pos += 1;
				}
				if(memo[i][j] < pos + memo[i+1][forTomorrow]){
					memo[i][j] = pos + memo[i+1][forTomorrow];
					choice[i][j] = useToday;
					nxtJ[i][j] = forTomorrow;
				}
			}
		}
	}
	printf("%d\n", memo[1][0]);
	int last = 0;
	for(int i = 1; i <= n; i++){
		print(i, last);
		last = nxtJ[i][last];
	}
	return 0;
}
