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
		- Nice Greedy problem

		- Consider that the first interval we want to choose is strictly to the right

		  (this can be done since we can consider to go to the left first by
		  
		  making a transformation to the intervals), then we would like to 

		  extend the maximum length each time.

		  For only positive integers case, we will have the maximum first, then 

		  the smallest, then the second maximum, and so on. Thus, we will 

		  have to go to the left after going to the right and viceversa, but

		  we will go the furthest we can each time, so, when going to the right

		  we will use the greatest L[i] that hasn't beed used yet and when going

		  left we will use the smallest R[i] that hasn't been used yet.

		- We can just simulate the idea and add all the valid segments until we cannot

		  move the way we want (we won't move to the right when choosing the corresponding
		  
		  L[i] or the opposite case with R[i]) or all the intervals have been used.

		- Finally, we update each interval (L[i],R[i]) with (-L[i],-R[i]) and

		  swap the values if the new L[i] > new R[i] and this will be the case

		  when our first interval is to the right.

		- Complexity: O(nlogn)

*/

const int N = 100000+5;

int n;
int L[N];
int R[N];
set<ii> Ls;
set<ii> Rs;

ll solve(){
	ll ans = 0LL;
	int position = 0;
	for(int i=1; i<=n; i++){
		int cur;
		if(i&1){ // Go right
			cur = (*Ls.rbegin()).second;
			if(L[cur] < position) break; // Can't go right, stop
			ans += L[cur] - position;
			position = L[cur];
		}
		else{ // Go left
			cur = (*Rs.begin()).second;
			if(position < R[cur]) break; // Can't go left, stop
			ans += position - R[cur];
			position = R[cur];
		}
		Ls.erase(mp(L[cur],cur));
		Rs.erase(mp(R[cur],cur));
	}
	ans += abs(position);
	return ans;
}

int main(){
	ri(n);
	for(int i=0; i<n; i++){
		ri2(L[i],R[i]);
		Ls.emplace(mp(L[i],i));
		Rs.emplace(mp(R[i],i));
	}
	ll ans = solve();
	Ls.clear(); Rs.clear();
	for(int i=0; i<n; i++){
		L[i] = -L[i];
		R[i] = -R[i];
		if(L[i] > R[i]) swap(L[i],R[i]);
		Ls.emplace(mp(L[i],i));
		Rs.emplace(mp(R[i],i));
	}
	ans = max(ans,solve());
	printf("%lld\n",ans);
	return 0;
}
