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
		- Classic Data Structures + Offline problem

		- First of all, make a Coordinate compression

		  for the X's to use a Fenwick Tree, so that 
		  
		  we can get some query for the range [L,R] 
		  
		  in any time. Use binary search to get the 
		  
		  position in the Fenwick Tree's indices.

		- The Offline part helps us to just use a 

		  two-pointers approach to answer queries.

		  Let's suppose that we are going to split

		  each query in 2:

		  Sum of all trees in [L,R] with height <= y2

		  - Sum of all trees in [L,R] with height < y1

		  So, each subquery will be:

		  Sum(L,R,y).

		- Now, just sort everything by greater height

		  and each time we'll answer a query, just

		  increase the position in the trees' vector

		  until we have the first one that has height

		  less or equal our Y and add it to the query's

		  answer.

		- Complexity: O((n+q)logn)

*/

const int N = 50000+5;

struct query{
	int L;
	int R;
	int H;
	int P;
	int id;
	query(){};
	query(int l, int r, int h, int p, int i){
		L = l;
		R = r;
		H = h;
		P = p;
		id = i;
	}
};

vi X;
int n;
int q;
vll F;
int len;
viii trees;
vector<query> queries;
ll ans[N];

bool compQ(query a, query b){
	return a.H > b.H;
}

bool comp(iii a, iii b){
	return a.second.second > b.second.second;
}

void update(int pos, int val){
	pos++;
	while(pos <= len){
		F[pos] += val;
		pos += (pos&(-pos));
	}
}

ll getSum(int pos){
	pos++;
	ll ans = 0LL;
	while(pos > 0){
		ans += F[pos];
		pos &= pos-1;
	}
	return ans;
}

ll getQuery(int L, int R){
	return getSum(R) - getSum(L-1);
}

int getPos(int x, int bound){
	int lo = 0, hi = len-1;
	while(lo < hi){
		int mi = lo + (hi-lo+bound)/2;
		if(X[mi] < x + bound) lo = mi + 1 - bound;
		else hi = mi - bound;
	}
	return lo;
}

void readData(){
	trees.clear();
	X.clear();
	queries.clear();

	ri(n);
	int a,b,c,d;
	int x,y;
	set<int> S;
	for(int i=0; i<n; i++){
		ri3(x,y,c);
		trees.pb(mp(c,mp(x,y)));
		S.insert(x);
	}
	for(set<int>::iterator it=S.begin(); it!=S.end(); it++){
		X.pb(*it);
	}
	len = X.size();
	ri(q);
	for(int i=0; i<q; i++){
		ans[i] = 0LL;
		ri2(a,b);
		ri2(c,d);
		queries.pb(query(a,c,b-1,-1,i));
		queries.pb(query(a,c,d,1,i));
	}
}

void preprocess(){
	sort(all(trees),comp);
	F.assign(len+1,0LL);
	sort(all(queries),compQ);
	for(int i=0; i<n; i++){
		int pos = getPos(trees[i].second.first,0);
		update(pos,trees[i].first);
	}
}

void solve(){
	int pos = 0;
	for(int i=0; i<queries.size(); i++){
		int L = queries[i].L;
		int R = queries[i].R;
		int H = queries[i].H;
		int P = queries[i].P;
		int id = queries[i].id;
		while(pos < n and trees[pos].second.second > H){
			int p = getPos(trees[pos].second.first,0);
			update(p,-trees[pos].first);
			pos++;
		}
		int l = getPos(L,0);
		if(X[l] < L or R < X[l]) continue;
		int r = getPos(R,1);
		ans[id] += 1LL*P*getQuery(getPos(L,0),getPos(R,1));
	}
}

int main(){
	int t;
	ri(t);
	int x,y,c;
	while(t--){
		readData();
		preprocess();
		solve();
		for(int i=0; i<q; i++){
			printf("%lld\n",ans[i]);
		}
	}
	return 0;
}
