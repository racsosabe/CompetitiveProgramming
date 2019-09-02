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
		- Interesting number theory + bitset problem.

		- Implementation according to the problem's tutorial by Radewoosh.

*/

const int N = 100000+2;
const int M = 7000+2;

int n, q;
bool primo[M];
bool sqfree[M];
bitset<7001> need[M];
bitset<7001> v[N];

void preprocess(){
	for(int i=1; i<=7000; i++){
		primo[i] = true;
		sqfree[i] = true;
	}
	primo[1] = false;
	sqfree[1] = true;
	for(int i=2; i*i<=7000; i++){
		if(primo[i]){
			for(int j = i+i; j<=7000; j+=i){
				primo[j] = false;
			}
		}
	}

	for(int i=1; i<=7000; i++){
		if(primo[i]){
			for(int j=i; j<=7000; j+=i){
				if((j / i) % i == 0) sqfree[j] = false;
			}
		}
	}
	for(int i=1; i<=7000; i++){
		for(int j=i; j<=7000; j+=i){
			if(sqfree[j / i]){
				need[i].set(j,1);
			}
		}
	}
}

int solve(int x, int y){
	int ans = (v[x]&need[y]).count();
	return ans&1;
}

void print(bitset<7001> &v){
	for(int i=1; i<=10; i++){
		cout << v[i];
	}
	puts("");
}

int main(){
	ri2(n,q);
	preprocess();
	int op, x, y, z;
	while(q--){
		ri(op);
		if(op == 1){
			ri2(x,y);
			v[x].reset();
			for(int i = 1; i*i<=y; i++){
				if(y % i == 0){
					v[x].set(i,1);
					v[x].set(y/i,1);
				}
			}
		}
		else if(op == 2){
			ri3(x,y,z);
			v[x] = (v[y]^v[z]);
		}
		else if(op == 3){
			ri3(x,y,z);
			v[x] = (v[y]&v[z]);
		}
		else{
			ri2(x,y);
			int ans = solve(x,y);
			putchar('0'+ans);
		}
	}
	puts("");
	return 0;
}
