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

const int N = 60;
const ll inf = 1LL<<60;

string s;
ll sumL[N];

void init(){
	sumL[0] = 0;
	for(int i = 1; i < N; i++){
		sumL[i] = sumL[i - 1] + ((1LL<<i) - (1LL<<(i - 1))) * i;
	}
}

ll getVal(string s){
	ll ans = 0LL;
	for(int i = 0; i < s.size(); i++){
		ans = (ans<<1) + s[i] - '0';
	}
	return ans;
}

ll getPos(ll x){
	int len = 63 - __builtin_clzll(x);
	return sumL[len] + (x - (1LL<<len)) * (len + 1);
}

string toString(ll x){
	string res = "";
	while(x > 0){
		res.push_back(char('0' + x % 2));
		x >>= 1;
	}
	reverse(all(res));
	return res;
}

ll getMax(string s){
	if(s[0] == '0') s = "1" + s;
	return getVal(s);
}

ll getMin(string s, int pos){
	string suffix = s.substr(0, pos + 1);
	string prefix = s.substr(pos + 1);
	int len = 0;
	ll res = inf;
	while(len <= prefix.size() and len <= suffix.size()){
		bool valid = true;
		for(int j = 0; j < len; j++){
			valid &= prefix[prefix.size() - 1 - j] == suffix[j];
		}
		if(!valid) break;
		string value = prefix + suffix.substr(len);
		ll cur_val = getVal(value);
		ll nxt_val = cur_val + 1;
		string total = toString(cur_val) + toString(nxt_val);
		bool can = false;
		for(int i = 0; i + s.size() - 1 < total.size(); i++){
			if(total.substr(i, s.size()) == s) can = true;
		}
		if(can){
			res = min(getPos(nxt_val) + (int)prefix.size(), res);
		}
		len += 1;
	}
	return res;
}

ll getBest(string s, int l, int r){
	string cur = s.substr(l, r - l + 1);
	ll x = getVal(cur);
	ll val = x;
	int leftR = s.size() - r - 1;
	ll res = getPos(val) + leftR;
	while(leftR > 0){
		val += 1;
		string nxt = toString(val);
		int take = min((int)nxt.size(), leftR);
		res = getPos(val) + leftR;
		cur += nxt.substr(0, take);
		leftR -= take;
	}
	int leftL = l;
	val = x;
	while(leftL > 0){
		val -= 1;
		if(val == 0) return inf;
		string prv = toString(val);
		int take = min((int)prv.size(), leftL);
		int pos = prv.size() - take;
		cur = prv.substr(pos, take) + cur;
		leftL -= take;
	}
	return cur == s? res : inf;
}

int main(){
	//freopen("infinitepatternmatching.in", "r", stdin);
	//freopen("infinitepatternmatching.out", "w", stdout);
	cin >> s;
	init();
	ll ans = getMax(s);
	for(int i = 0; i + 1 < s.size(); i++){
		ans = min(ans, getMin(s, i));
	}
	for(int i = 0; i < s.size(); i++){
		if(s[i] == '0') continue;
		for(int j = i; j < s.size(); j++){
			ans = min(ans, getBest(s, i, j));
		}
	}
	printf("%lld\n", ans);
	return 0;
}
