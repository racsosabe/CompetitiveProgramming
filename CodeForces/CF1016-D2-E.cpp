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
		- Just notice that we only care about the fences' lengths, so set a
		  cumulative sum of lengths to access them in O(1).

		- Now, we need to now the possible lines that will affect the point
		  according to the source, so we get the range of intersection

		  for the lines (a,s) to (x,y) and (b,s) to (x,y) (Let's say without
		  loss of generality that a < b) with the OX.

		- Once we did that (we can get the intersections in O(1), denoted by
		  
		  x1 and x2), we only need to sum up the lengths of fences in the

		  interval [x1,x2] and the final time we will answer is the relationship

		  between heights (transform coefficient = (y-s)/y since s < 0)
		
		- Complexity: O(qlogn) the log is for binary searching limits of fences.

*/

const int N = 200000+5;

int n,q;
int s,a,b;
ii v[N];
int ac[N];

double getInt(int a, int b, int c, int d){
	double t = -1.0*b/(d-b);
	return t*(c-a)+a;
}

double intersection(double a, double b, double c, double d){
	if(b < c) return 0;
	if(d < a) return 0;
	double x1 = max(a,c);
	double x2 = min(b,d);
	return max(x2-x1,0.0);
}

int main(){
	ri3(s,a,b);
	if(a > b) swap(a,b);
	ri(n);
	int x,y;
	for(int i=1; i<=n; i++){
		ri2(x,y);
		v[i] = mp(x,y);
		ac[i] = ac[i-1] + y-x;
	}
	ri(q);
	while(q--){
		ri2(x,y);
		double coef = 1.0*(y-s)/y;
		double x1 = getInt(x,y,a,s);
		double x2 = getInt(x,y,b,s);
		if(v[n].second < x1 or x2 < v[1].first) puts("0.0000000");
		else{
			int lo = 1 , hi = n;
			while(lo < hi){
				int mi = lo + (hi-lo+1)/2;
				if(v[mi].first <= x1) lo = mi;
				else hi = mi-1;
			}
			int lower = lo;
			hi = n;
			while(lo < hi){
				int mi = lo + (hi-lo+1)/2;
				if(v[mi].first <= x2) lo = mi;
				else hi = mi-1;
			}
			int upper = lo;
			double sum = 0.0;
			if(lower == upper){
				sum = intersection(v[lower].first,v[lower].second,x1,x2);
			}
			else{
				if(upper-1 >= lower){
					sum += ac[upper-1] - ac[lower];
				}
				sum += intersection(v[lower].first,v[lower].second,x1,x2);
				sum += intersection(v[upper].first,v[upper].second,x1,x2);
			}
			sum *= coef;
			cout << setprecision(7) << fixed << sum << endl;
		}
	}
	return 0;
}
