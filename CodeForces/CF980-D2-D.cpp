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

		- Math and brute force problem.

		- Let's say that we get a "Square Free Representation (SFR)" of each number:
		  SFR(N) = p1^{a1}p2^{a2}...pk^{ak}

		  Where each ai is the original exponent in N modulo 2.

		  So, if we want to make groups as required, only the ones with the same SFR will go into the same group.

		  Tricky case: 0s are allowed to join any group (since 0 is a square and a.0 = 0)

		  Brute force for each interval and get the number of different 
		  
		  SFR (associated with a low number to use arrays and avoiding LogN factors).

		  Consider the tricky case and done.
*/

const int N = 5000+5;

int n;
int v[N];
int ans[N];
map<int,int> color;

int SquareFree(int x){
	if(x == 0) return 0;
	int ans = 1;
	if(x < 0) ans = -ans;
	x = abs(x);
	for(int i=2; i*i<=x; i++){
		if(x%i==0){
			int p = 0;
			while(x%i==0){
				x /= i;
				p^=1;
			}
			if(p) ans *= i;
		}
	}
	if(x!=1){
		ans *= x;
	}
	return ans;
}

int main(){
	ri(n);
	for(int i=0; i<n; i++){
		ri(v[i]);
		v[i] = SquareFree(v[i]);
	}
	int c = 1;
	for(int i=0; i<n; i++){
		if(color[v[i]]){
			v[i] = color[v[i]];
		}
		else{
			color[v[i]] = c;
			v[i] = c++;
		}
	}
	int cero = color[0];
	for(int i=0; i<n; i++){
		int Q[N] = {0};
		int act = 0;
		for(int j=i; j<n; j++){
			if(Q[v[j]]) Q[v[j]]++;
			else{
				Q[v[j]]++;
				act++;
			}
			if(Q[cero] == 0) ans[act]++;
			else if(Q[cero] != j-i+1) ans[act-1]++;
			else ans[1]++;
		}
	}
	for(int i=1; i<=n; i++){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
