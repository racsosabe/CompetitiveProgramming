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

	- Notice that since we want the sum of values of all the intervals that have

	  a non-empty intersection with [A, B], the answer is equivalent to the total

	  sum of values minus the sum of values of the intervals that don't intersect

	  at all with [A, B].

	- An interval [l, r] doesn't intersect with [A, B] if and only if:

	  1) r < A or

	  2) B < l

	- We can mantain two Fenwick Trees:

	  1) This one will store the sum of values of the intervals that end in position x

	  2) This one will store the sum of values of the intervals that start in position x

	- Thus, the answer for query [A, B] will be:

	  Ans = Total sum - query(1, 0, A - 1) - query(2, B + 1, MAX)

	  Where query(id, l, r) gives the sum of the positions [l, r] in the Fenwick

	  Tree with id "id". MAX = 10^6 due to constraints.

	- Complexity: O(nlogMAX)

*/

const int N = 100000 + 5;
const int limit = 1000000;

int n;
int q;
int lower[N];
int upper[N];
int price[N];
ll ft[2][10 * N];

void update(int id, int pos, int val){
	pos += 1;
	while(pos <= limit + 1){
		ft[id][pos] += val;
		pos += (-pos) & pos;
	}
}

ll getSum(int id, int pos){
	pos += 1;
	ll res = 0LL;
	while(pos > 0){
		res += ft[id][pos];
		pos &= pos - 1;
	}
	return res;
}

ll query(int id, int l, int r){
	return getSum(id, r) - getSum(id, l - 1);
}

int main(){
	ri(n);
	ll total_sum = 0LL;
	for(int i = 1; i <= n; i++){
		ri3(lower[i], upper[i], price[i]);
		total_sum += price[i];
		update(0, upper[i], price[i]);
		update(1, lower[i], price[i]);
	}
	ri(q);
	int op;
	int i, l, r, c;
	while(q--){
		ri(op);
		if(op == 1){
			ri2(l, r);
			printf("%lld\n", total_sum - query(0, 0, l - 1) - query(1, r + 1, limit + 1));
		}
		else{
			ri(i);
			ri3(l, r, c);
			total_sum -= price[i];
			update(0, upper[i], -price[i]);
			update(1, lower[i], -price[i]);
			lower[i] = l;
			upper[i] = r;
			price[i] = c;
			total_sum += price[i];
			update(0, upper[i], price[i]);
			update(1, lower[i], price[i]);
		}
	}
	return 0;
}
