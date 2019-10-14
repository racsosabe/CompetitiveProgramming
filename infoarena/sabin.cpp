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
		- Nice strings & implementation problem.

		- First of all, we just need the number of times the minimum of all the maxprefix

		  is at least x and then we substract the number of times the minimum
		  
		  is at least (x+1).

		- We may use any expected O(1) way to store these frequencies. 

		  Now, if we want the minimum of maxprefix to be at least a value x

		  we will need to have the prefix of size x of each string in the set

		  so we can just concatenate these strings (conveniently) and add

		  that string to the frequency map.

		  The way to encode the prefixes in this code is to store the i-th characters

		  of each string in the set continuously in the final string. Just to

		  have an exactly O(npk) complexity of precomputation.

		- Finally, we will just get the wanted values and get the answer.

		- Complexity: O((n+m)pk)

*/

const int K = 20;
const int P = 35;
const int M = 30000+5;

int n, k, m, p, q;
int a[K];
char carry[K][P];
char shelf[M][P];
unordered_map<string,int> F;

int main(){
	freopen("sabin.in","r",stdin);
	freopen("sabin.out","w",stdout);
	ri3(n,k,m);
	ri2(p,q);
	for(int i=0; i<n; i++){
		for(int j=0; j<k; j++){
			scanf("%s",carry[j]);
		}
		string s = "";
		F[s] += 1;
		for(int x = 1; x <= p; x++){
			for(int j=0; j<k; j++){
				s.push_back(carry[j][x-1]);
			}
			F[s] += 1;
		}
	}
	for(int i=1; i<=m; i++){
		scanf("%s",shelf[i]);
	}
	int x;
	int id;
	string v;
	string w;
	while(q--){
		ri(x);
		v = "";
		for(int i=0; i<k; i++){
			ri(a[i]);
		}
		int limit = x <= p? x : p;
		for(int i=1; i<=limit; i++){
			for(int j=0; j<k; j++){
				v.push_back(shelf[a[j]][i-1]);
			}
		}
		w = v;
		if(x < p){
			for(int j=0; j<k; j++){
				w.push_back(shelf[a[j]][x]);
			}
		}
		printf("%d\n",F[v] - F[w]);
	}
	return 0;
}
