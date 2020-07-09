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

	- Binary Indexed Tree problem

	- First of all, consider fixing the index k (must be greater than or equal to 3
	
	  since i < j < k would be possible that way), then try to count all the 

	  valid i's.

	  How to count the number of valid i's? Simple, just check that there will

	  exist an index j in the range [i + 1, k - 1] that has a 1. Now, that could

	  be a little tricky, but don't worry, let's divide the different possible

	  cases:

	  1) The string [i, k] has exactly one 1: This can be computed solely apart

	     by multiplying the number of zeros to the left and to the right each

	     1.

	  2) The string [i, k] has more than one 1: This can be computed just by

	     
	     counting the number of subarrays [i, k] with odd number of ones >= 3.

	     Notice that this wouldn't help for the case 1 since there could be 

	     degenerate cases like 100 in which we can't choose i < j < k correctly.

	     We can just analyze each subarray as a difference of prefixes:

	     	ones[i, k] = prefix[k] - prefix[i-1]

	     This can be done using two BITs (one for odd prefixes and the other for the even
	    
	     ones)

	     And just computing all the prefixes with a different parity and with

	     value <= prefix[k] - 3.

	  - Complexity: O(nlogn) per case
*/

const int N = 200000+5;

int n;
char s[N];
int ft[3][N];
int prefix[N];

void update(int id, int pos, int val){
	pos++;
	while(pos <= n + 1){
		ft[id][pos] += val;
		pos += (-pos) & pos;
	}
}

int query(int id, int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[id][pos];
		pos &= pos-1;
	}
	return res;
}

void clearAll(){
	for(int i=0; i<=n+1; i++){
		ft[0][i] = ft[1][i] = 0;
	}
}

int main(){
	int t;
	ri(t);
	while(t--){
		ri(n);
		scanf("%s", s + 1);
		ll ans = 0LL;
		vector<int> ones;
		for(int i=1; i<=n; i++){
			if(s[i] == '1'){
				ones.emplace_back(i);
			}
		}
		ones.emplace_back(n + 1);
		for(int i = 0; i + 1 < ones.size(); i++){
			ans += 1LL * (ones[i] - (i? ones[i - 1] + 1 : 1)) * (ones[i + 1] - ones[i] - 1);
		}
		for(int i=1; i<=n; i++){
			prefix[i] = prefix[i-1] + s[i] - '0';
		}
		update(0, 0, 1);
		for(int i=1; i<=n; i++){
			int want = prefix[i] - 3;
			int need = (prefix[i] & 1) ^ 1;
			int act = query(need, want);
			ans += act;
			update(prefix[i] & 1, prefix[i], 1);
		}
		printf("%lld\n", ans);
		if(t) clearAll();
	}
	return 0;
}
