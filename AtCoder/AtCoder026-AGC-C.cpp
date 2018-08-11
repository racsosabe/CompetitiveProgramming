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

/*
	Author: Racso Galvan

	Idea: 
		- Good Meet in the middle/Brute Force problem.
		
		- Let's use the fact that n is really small, so we can split the

		  string in two parts, so that if we got the first N characters'

		  colors, then we'll know what is needed to colored after.

		  Since we get the X first and the Y last characters of it and

		  X + Y = n

		- Now, we can use different ways to map them, but in this case I

		  wanted to use a Trie that mantains frequency for each string of 
		  length n formed in the first half, but in a specific way:

		  act = (characters needed for color 1) + (characters needed for color 0)
		  We see that the first part are the Y characters from right to left
		  and the second one are the X characters from left to right.

		- Also, since a string can be formed in different colorings, we must
		  take the frequency according to that (let's say that we relate them 
		  to a pair (Y,X))

		- With all the above, we can brute force the last half and add the
		  queries according to what's needed.

		- Complexity: O(n logn 2^{n}) since we are using map for the frequencies.

*/

const int N = 40;
const int MAX = 4800000;
const int E = 26;

int n;
int nodos = 1;
char s[N];
char act[N];
int trie[MAX][E];
map<ii,int> frequency[MAX];

void insert(int q1, int q2){
	int pos = 0;
	for(int i=0; i<n; i++){
		int next = act[i]-'a';
		if(!trie[pos][next]) trie[pos][next] = nodos++;
		pos = trie[pos][next];
	}
	frequency[pos][mp(q1,q2)]++;
}

int query(int q1, int q2){
	int pos = 0;
	for(int i=0; i<n; i++){
		int next = act[i]-'a';
		if(!trie[pos][next]) return 0;
		pos = trie[pos][next];
	}
	return frequency[pos][mp(q1,q2)];
}

int main(){
	ri(n);
	scanf("%s",s);
	for(int mask=0; mask<1<<n; mask++){
		int p = 0;
		for(int j=n-1; j>=0; j--){
			if((mask>>j)&1) continue;
			act[p++] = s[j];
		}
		for(int j=0; j<n; j++){
			if((mask>>j)&1){
				act[p++] = s[j];
			}
		}
		act[n] = '\0';
		insert(n-__builtin_popcount(mask),__builtin_popcount(mask));
	}
	ll ans = 0LL;
	for(int mask=0; mask<1<<n; mask++){
		int p = 0;
		for(int j=0; j<n; j++){
			if((mask>>j)&1){
				act[p++] = s[j+n];
			}
		}
		for(int j=n-1; j>=0; j--){
			if((mask>>j)&1) continue;
			act[p++] = s[j+n];
		}
		act[n] = '\0';
		ans += query(__builtin_popcount(mask),n-__builtin_popcount(mask));
	}
	cout << ans << endl;
	return 0;
}
