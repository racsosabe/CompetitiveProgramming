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
	
		- Good math and sliding windows problem.

		- Just maximize for each consecutive K coordinates (sorting before)
		  the formula:

		  	$$ \sum\limits_{i=0}^{k-1}i\cdot x_{i} - \sum\limits_{i=0}^{k-1}(k-1-i)\cdot x_{i} $$

		  Use the first sum as V1, and the second one as V2. Deduce how to transform it.
		  Use deque to handle the modifications easily (sliding windows).

*/

const int N = 300000+5;

int n,k;
int x[N];

int main(){
	ri(n);
	vii coord;
	for(int i=0; i<n; i++){
		ri(x[i]);
		coord.pb(mp(x[i],i));
	}
	sort(all(coord));
	ri(k);
	int L = 0, R = k-1;
	ll ans = 0LL;
	deque<int> Q;
	ll V1 = 0LL;
	ll V2 = 0LL;
	ll S = 0LL;
	for(int i=0; i<k; i++){
		Q.push_back(i);
		V1 += i*coord[i].first;
		V2 += (k-1-i)*coord[i].first;
		ans = V1-V2;
		S += coord[i].first;
	}
	for(int i=k; i<n; i++){
		int x0 = Q.front(); Q.pop_front();
		int xkp1 = i;
		ll new_V1 = V1 - S + coord[x0].first + 1LL*(k-1)*coord[xkp1].first;
		ll new_V2 = V2 + S - 1LL*k*coord[x0].first;
		ll new_S = S - coord[x0].first + coord[xkp1].first;
		if(ans > new_V1 - new_V2){
			ans = new_V1 - new_V2;
			R = i;
			L = i-k+1;
		}
		Q.push_back(i);
		S = new_S;
		V1 = new_V1;
		V2 = new_V2;
	}
	for(int i=L; i<=R; i++){
		printf("%d ",coord[i].second+1);
	}
	return 0;
}
