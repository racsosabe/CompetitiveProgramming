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

	- Implementation problem + Fast I/O.

	- Just store the strings with exchange rate in a map.

	- Complexity: O((n + m)logn|s|) where |s| is the maximum size of the strings per test.

*/

const int N = 100000+5;

int n, m;
double r[N];
map<string, int> change;

string readString(){
	char c = getchar();
	string ans = "";
	while(c != ' ' and c != '\n'){
		ans.push_back(c);
		c = getchar();
	}
	return ans;
}

double readDouble(){
	char c = getchar();
	double ans = 0.0;
	double p = 0.1;
	bool decimal = false;
	while(c != ' ' and c != '\n'){
		if(c == '.'){
			decimal = true;
		}
		else{
			if(decimal){
				ans += p * (c - '0');
				p *= 0.1;
			}
			else{
				ans = 10 * ans + c - '0';
			}
		}
		c = getchar();
	}
	return ans;
}

int main(){
	int t;
	ri(t);
	string s;
	r[0] = 1.0;
	while(t--){
		ri2(n, m);
		change.clear();
		change["JD"] = 0;
		getchar();
		for(int i=1; i<=n; i++){
			s = readString();
			r[i] = readDouble();
			change[s] = i;
		}
		double ans = 0.0;
		for(int i=0; i<m; i++){
			double amount;
			amount = readDouble();
			s = readString();
			ans += r[change[s]] * amount;
		}
		cout << setprecision(6) << fixed << ans << endl;
	}
	return 0;
}
