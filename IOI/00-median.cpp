#include<bits/stdc++.h>
#include "device.h"
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

	- Quick Sort variation for finding median. Very interesting problem.

	- First of all, since the queries are made using 3 positions, we need to pivots

	  a and b to partition the indices:

	  [L] a [M] b [R]

	  Where L, M and R are vectors of indices.

	- Now, with the first a and b chosen (randomly) we've got a partial order

	  relation R, such that:

	  x R a and a R y for every x in L and y in M U {b} U R

	  x R b and b R y for every x in L U {a} U M and y in R.

	- Thus, we can chose two elements x, y in any vector L, M and R and check easily

	  wether x R y or y R x with one Med3 query considering the 3rd index as a

	  if x, y are in L or M or b if x, y are in R.

	- Now, we can ignore some elements from the current partition since we can

	  guarantee that they can't be the answer. Let's use two variables wantL and 

	  wantR to represent how many elements to the left and right (respectively) must

	  have our answer in the partition.

	- We will have only 5 possible situations:

	  * Our answer is a: This happens when |L| = wantL
	  * Our answer is b: This happens when |R| = wantR
	  * Our answer is in L: 
	    1) If wantL = 0 and |L| = 1, the answer is the only element in L
	    2) If |R| + |M| + 1 < wantR, we can ignore those values and make a new

	       partition in L, considering that wantR will have to be reduced by 

	       |R| + |M| + 2 (vectors R, M and elements a and b). We can choose 

	       randomly two elements x, y in L and swap them if y R x to build the

	       new partition. 
	  * Our answer is in M: 
	    1) If |L| + 1 = wantL and |M| = 1, the answer is the only element in M
	    2) If |R| + |M| + 1 >= wantR and |L| + |M| + 1 >= wantL, we can ignore the

	       values in L and R and elements a and b by making a partition in M,

	       the partition is built exactly as the case for L.
	  * Our answer is in R: 
	    1) If wantR = 0 and |R| = 1, the answer is the only element in R

	    2) If |L| + |M| + 1 < wantL, we can ignore those values by making a 

	       partition in R.
	
	- This is a little variation of Quicksort algorithm.

	- Complexity: O(nlogn) expected.
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l,r)(rng);
}

void makePartition(vi &v, int a, int b, vi &L, vi &M, vi &R){
	for(auto x : v){
		if(x == a or x == b) continue;
		int m = Med3(a, b, x);
		if(m == a) L.emplace_back(x);
		else if(m == b) R.emplace_back(x);
		else M.emplace_back(x);
	}
}

int solve(int a, int b, int wantL, int wantR, vi &L, vi &M, vi &R){
	assert(L.size() + M.size() + R.size() + 2 == wantL + wantR + 1);
	if(L.size() == wantL) return a;
	if(R.size() == wantR) return b;
	if(L.size() + 1 == wantL and M.size() == 1) return M.back();
	if(wantL == 0 and L.size() == 1) return L.back();
	if(wantR == 0 and R.size() == 1) return R.back();
	if(L.size() + M.size() + 1 < wantL){
		vector<int> newL;
		vector<int> newM;
		vector<int> newR;
		int new_a = R[random(0, R.size() - 1)];
		int new_b = R[random(0, R.size() - 1)];
		while(new_a == new_b) new_b = R[random(0, R.size() - 1)];
		int m = Med3(new_a, new_b, b);
		if(m == new_b) swap(new_a, new_b);
		int new_wantL = wantL - 1 - L.size() - M.size() - 1;
		int new_wantR = wantR;
		makePartition(R, new_a, new_b, newL, newM, newR);
		L.clear();
		M.clear();
		R.clear();
		return solve(new_a, new_b, new_wantL, new_wantR, newL, newM, newR);
	}
	else if(R.size() + M.size() + 1 < wantR){
		vector<int> newL;
		vector<int> newM;
		vector<int> newR;
		int new_a = L[random(0, L.size() - 1)];
		int new_b = L[random(0, L.size() - 1)];
		while(new_a == new_b) new_b = L[random(0, L.size() - 1)];
		int m = Med3(new_a, new_b, a);
		if(m == new_a) swap(new_a, new_b);
		int new_wantL = wantL;
		int new_wantR = wantR - 1 - R.size() - M.size() - 1;
		makePartition(L, new_a, new_b, newL, newM, newR);
		L.clear();
		M.clear();
		R.clear();
		return solve(new_a, new_b, new_wantL, new_wantR, newL, newM, newR);
	}
	else{
		vector<int> newL;
		vector<int> newM;
		vector<int> newR;
		int new_a = M[random(0, M.size() - 1)];
		int new_b = M[random(0, M.size() - 1)];
		while(new_a == new_b) new_b = M[random(0, M.size() - 1)];
		int m = Med3(new_a, new_b, a);
		if(m == new_b) swap(new_a, new_b);
		int new_wantL = wantL - L.size() - 1;
		int new_wantR = wantR - R.size() - 1;
		makePartition(M, new_a, new_b, newL, newM, newR);
		L.clear();
		M.clear();
		R.clear();
		return solve(new_a, new_b, new_wantL, new_wantR, newL, newM, newR);
	}
}

int Median(int n){
	int a = random(1, n);
	int b = random(1, n);
	while(a == b) b = random(1, n);
	vector<int> L, M, R;
	for(int i = 1; i <= n; i++){
		if(i == a or i == b) continue;
		int m = Med3(a, b, i);
		if(m == a) L.emplace_back(i);
		else if(m == b) R.emplace_back(i);
		else M.emplace_back(i);
	}
	return solve(a, b, (n - 1) / 2, (n - 1) / 2, L, M, R);
}
