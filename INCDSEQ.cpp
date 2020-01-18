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
const long long MOD = 5000000;

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

const int N = 10000+5;
const int MAX = 100000+5;
const int K = 50 + 5;

int n, k;
int a[N];
int memo[K][N];
int last[MAX];
int ft[K][MAX];

void update(int id, int pos, int val){
	pos++;
	while(pos < MAX){
		ft[id][pos] = add(ft[id][pos],val);
		pos += (-pos) & pos;
	}
}

int query(int id, int pos){
	pos++;
	int ans = 0;
	while(pos > 0){
		ans = add(ans,ft[id][pos]);
		pos &= pos-1;
	}
	return ans;
}

void compress(){
	set<int> S;
	for(int i=0; i<=n; i++){
		S.emplace(a[i]);
	}
	map<int,int> id;
	int len = 0;
	for(auto x : S){
		id[x] = len++;
	}
	for(int i=0; i<=n; i++){
		a[i] = id[a[i]];
	}

}

int main(){
	ri2(n,k);
	int ans = 0;
	memset(last,-1,sizeof last);
	for(int i=1; i<=n; i++){
		ri(a[i]);
		a[i] += 1;
	}
	compress();
	update(0,a[0],1);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=k; j++){
			memo[j][i] = query(j-1,a[i]-1);
			if(last[a[i]] != -1){
				update(j,a[i],add(memo[j][i], MOD - memo[j][last[a[i]]]));
			}
			else{
				update(j,a[i],memo[j][i]);
			}
			if(j == k){
				int res = memo[j][i];
				if(last[a[i]] != -1){
					res = add(res, MOD - memo[j][last[a[i]]]);
				}
				ans = add(ans,res);
			}
		}
		last[a[i]] = i;
	}
	cout << ans << endl;
	return 0;
}
