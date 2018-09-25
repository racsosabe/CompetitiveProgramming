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

ll add(ll a, ll b, ll m = MOD){ return (a%m + b%m+2*m)%m;}

ll mul(ll a, ll b, ll m = MOD){ return ((a%m+m)*(b%m+m))%m;}

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

const int N = 1000000+5;
const int B = 900;
const int M = (500000+B-1)/B;
const int L = 31;
const int E = 3;

class Trie{
	int nodes;
	int table[M*L+5][E];
	int frec[M*L+5];
	public:
	Trie(){
		nodes = 0;
		frec[0] = 0;
		table[0][0] = table[0][1] = 0;
	};

	void reset(){
		nodes = 0;
		frec[0] = 0;
		table[0][0] = table[0][1] = 0;
	}

	void insert(ll x){
		int pos = 0;
		for(int i=31; i>=0; i--){
			int next = ((x>>i)&1);
			if(table[pos][next] == 0){
				table[pos][next] = ++nodes;
				table[nodes][0] = table[nodes][1] = 0;
				frec[nodes] = 0;
			}
			pos = table[pos][next];
			frec[pos]++;
		}
	}

	pair<ll,ll> getMaxXor(ll x){
		int pos = 0;
		ll value = 0;
		ll XOR = 0;
		for(int i=31; i>=0; i--){
			int wanted = !((x>>i)&1);
			if(table[pos][wanted] == 0) wanted ^= 1;
			if(wanted){
				if(!((x>>i)&1)){
					XOR ^= 1LL<<i;
				}
				value ^= 1LL<<i;
			}
			else{
				if((x>>i)&1){
					XOR ^= 1LL<<i;
				}
			}
			pos = table[pos][wanted];
		}
		return mp(XOR,value);
	}

	int getLessOrEqual(ll x){
		int pos = 0;
		int ans = 0;
		for(int i=31; i>=0; i--){
			int next = (x>>i)&1;
			int L = table[pos][0];
			if(next){
				ans += frec[L];
			}
			pos = table[pos][next];
			if(pos == 0) break;
		}
		ans += frec[pos];
		return ans;
	}

};

int n = 0;
int v[N];
int b = B;
int buckets = -1;
Trie SQRT[M+5];

void addAtTheEnd(int x){
	v[n] = x;
	if(n%b == 0){
		buckets++;
	}
	SQRT[n/b].insert(x);
	n++;
}

void maximizeXor(int l, int r, int x){
	ll max_xor = -1;
	ll ans = 0;
	while(l%b and l < r){
		if(max_xor < 1LL*(x^v[l])){
			max_xor = x^v[l];
			ans = v[l];
		}
		l++;
	}
	while(l + b <= r){
		pair<ll,ll> carry = SQRT[l/b].getMaxXor(x);
		if(max_xor < carry.first){
			max_xor = carry.first;
			ans = carry.second;
		}
		l += b;
	}
	while(l <= r){
		if(max_xor < 1LL*(x^v[l])){
			max_xor = 1LL*(x^v[l]);
			ans = 1LL*v[l];
		}
		l++;
	}
	printf("%lld\n",ans);
}

void deleteLastK(int k){
	int new_n = max(0,n - k);
	if(new_n % b == 0){
		for(int no_bucket=new_n/b; no_bucket <= buckets; no_bucket++){
			SQRT[no_bucket].reset();
		}
	}
	else{
		for(int no_bucket=new_n/b; no_bucket <= buckets; no_bucket++){
			SQRT[no_bucket].reset();
		}
		for(int pos=(new_n - new_n%b); pos<new_n; pos++){
			SQRT[new_n/b].insert(v[pos]);
		}
	}
	n = new_n;
	buckets = n > 0?(n-1)/b:-1;
}

int lessOrEqualThan(int l, int r, int x){
	int ans = 0;
	while(l%b and l < r){
		if(v[l] <= x) ans++;
		l++;
	}
	while(l + b <= r){
		ans += SQRT[l/b].getLessOrEqual(x);
		l += b;
	}
	while(l <= r){
		if(v[l] <= x) ans++;
		l++;
	}
	return ans;
}

void getKth(int l, int r, int x){
	int lo = 1, hi = 500000;
	while(lo < hi){
		int mi = lo + (hi-lo)/2;
		if(lessOrEqualThan(l,r,mi) < x) lo = mi+1;
		else hi = mi;
	}
	printf("%d\n",lo);
}

int main(){
	int q;
	ri(q);
	int op;
	int l,r,x;
	while(q--){
		ri(op);
		switch(op){
			case 0: ri(x); addAtTheEnd(x); break;
			case 1: ri3(l,r,x); l--; r--; if(l > r) swap(l,r); maximizeXor(l,r,x); break;
			case 2: ri(x); deleteLastK(x); break;
			case 3: ri3(l,r,x); l--; r--; if(l > r) swap(l,r); printf("%d\n",lessOrEqualThan(l,r,x)); break;
			case 4: ri3(l,r,x); l--; r--; if(l > r) swap(l,r); getKth(l,r,x); break;
		}	
	}
	return 0;
}
