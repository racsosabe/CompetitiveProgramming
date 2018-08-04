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
		- Good DP and Binary Search problem.

		- First, we need that all the letters in s appear in t, else the answer
		  is immediately No.

		- Now, let's store the appearances for each letter in t in vectors.
		  This will help us later.

		- So, let's denote two functions preffix(i) and suffix(i), which

		  give the longest preffix or suffix subsequence that is a substring of t
		  and end/start in position i.

		  That means, that if we are in position i with letter s[i], we

		  only need to know the best preffix USING letter s[i].

		  This position can be binary searched with the appearances vectors.
		
		  Then, let's say that we have gotten the position K, so we only

		  need to check if

		  K + suffix(i+1) >= t.size

		  for each letter s[i], they all must be true to get a "Yes".

*/

const int N = 200000+5;

int n,m;
string s,t;
int suffix[N];
int preffix[N];
vi appear[30];

int main(){
	cin >> s >> t;
	n = s.size();
	m = t.size();
	for(int i=1; i<=t.size(); i++){
		appear[t[i-1]-'a'].pb(i);
	}
	bool can = true;
	for(int i=0; i<s.size(); i++){
		if(appear[s[i]-'a'].size()) continue;
		can = false;
	}
	if(can){
		for(int i=1; i<=s.size(); i++){
			int max_subsequence = preffix[i-1];
			if(max_subsequence < t.size() and t[max_subsequence] == s[i-1]){
				max_subsequence++;
			}
			preffix[i] = max_subsequence;
		}
		for(int i=s.size(); i>=1; i--){
			int max_subsequence = suffix[i+1];
			if(max_subsequence < t.size() and t[t.size()-1-max_subsequence]==s[i-1]){
				max_subsequence++;
			}
			suffix[i] = max_subsequence;
		}
		for(int i=1; i<=s.size(); i++){
			char x = s[i-1];
			int lo = 0, hi = appear[x-'a'].size()-1;
			while(lo < hi){
				int mi = lo + (hi-lo+1)/2;
				if(appear[x-'a'][mi] <= preffix[i]) lo = mi;
				else hi = mi-1;
			}
			int here = appear[x-'a'][lo];
			int rest = suffix[i+1];
			if(here+rest >= t.size()) continue;
			can = false;
		}
		if(can) puts("Yes");
		else puts("No");
	}
	else puts("No");
	return 0;
}
