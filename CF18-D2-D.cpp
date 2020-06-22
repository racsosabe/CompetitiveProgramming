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

const int MAX = 2000+5;

struct BigInt{
	int len;
	vi v;

	BigInt(){
		len = 1;
		v = {0};
	}

	BigInt(int x){
		if(x == 0){
			len = 1;
			v = {0};
		}
		else{
			while(x > 0){
				v.emplace_back(x % 10);
				x /= 10;
			}
			len = v.size();
		}
	}

	BigInt(vi a){
		len = a.size();
		v = a;
	}

	void operator += (BigInt a) {
		vi new_v(max(a.len, len),0);
		for(int i=0; i<new_v.size(); i++){
			if(i < len) new_v[i] += v[i];
			if(i < a.len) new_v[i] += a.v[i];
		}
		for(int i=0; i<new_v.size(); i++){
			if(new_v[i] > 9){
				if(i + 1 < new_v.size()){
					new_v.emplace_back(new_v[i] / 10);
				}
				else{
					new_v[i+1] += new_v[i] / 10;
				}
				new_v[i] %= 10;
			}
		}
		while(new_v.back() == 0 and new_v.size() > 1) new_v.pop_back();
		v = new_v;
		len = v.size();
	};

	void operator = (BigInt a) {
		len = a.len;
		v = a.v;
	}

	BigInt operator + (BigInt a) const {
		vi new_v(max(a.len, len),0);
		for(int i=0; i<new_v.size(); i++){
			if(i < len) new_v[i] += v[i];
			if(i < a.len) new_v[i] += a.v[i];
		}
		for(int i=0; i<new_v.size(); i++){
			if(new_v[i] > 9){
				if(i + 1 == new_v.size()){
					new_v.emplace_back(new_v[i] / 10);
				}
				else{
					new_v[i+1] += new_v[i] / 10;
				}
				new_v[i] %= 10;
			}
		}
		while(new_v.back() == 0 and new_v.size() > 1) new_v.pop_back();
		return BigInt(new_v);
	};

	bool operator == (BigInt a) const {
		return v == a.v;
	};

	bool operator < (BigInt a) const {
		if(len == a.len){
			for(int i=len-1; i>=0; i--){
				if(v[i] < a.v[i]) return true;
				if(v[i] > a.v[i]) return false;
			}
			return false;
		}
		return len < a.len;
	};

	void print(){
		for(int i=len-1; i>=0; i--){
			putchar('0' + v[i]);
		}
		puts("");
	}
};

const int N = 5000+5;
const int M = 2000+5;

int n;
vi pos[M];
char s[10];
BigInt pot[M];
BigInt memo[N];
BigInt prefix[N];

int main(){
	pot[0] = BigInt(1);
	for(int i=1; i<M; i++) pot[i] = pot[i-1] + pot[i-1];
	ri(n);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%s %d",s,&x);
		if(s[0] == 'w'){
			pos[x].emplace_back(i);
		}
		else{
			for(auto p : pos[x]){
				BigInt cand = pot[x] + prefix[p-1];
				if(memo[i] < cand) memo[i] = cand;
			}
		}
		prefix[i] = prefix[i-1] < memo[i]? memo[i] : prefix[i-1];
	}
	prefix[n].print();
	return 0;
}
