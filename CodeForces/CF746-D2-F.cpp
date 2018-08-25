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
		- Good Two Pointers problem.

		- First, realize that the problem can be expressed as getting the
		  subarray such that the sum of the half ceil of the maximum w values
		  and the sum of the other ones is less or equal than k and it's pleasure
		  is maximum.
		
		- We can use two pointers to mantain the arrays, using every start point L
		  possible and only extending R if possible (since R is always increasing
		  we can recycle it, that's why it's two pointers).

		- Now, we need to use 2 sets to mantain the maximum w elements in one (partly)
		  and the other ones in the other one (full).

		  For each value T to insert, it can be

		  T >= min(partly[i]) for all elements in partly

		  or T < min(partly[i]).

		- To handle with the first case, just add the value to partly and take off
		  its minimum value, for any other case just add T to the 'full' set
		  and modify the values of Duration and Pleasure obtained.

		- To avoid wrong assignments, we use the Insert operation as a boolean
		  so that we return true if the insertion is valid (will give a new 
		  duration <= k), so we use this to check the extension of R.
		
		  In addition, once we checked the insertion is right, use boolean commit
		  to actually perform insertion in the sets.

		- Complexity: O(nlogn).

*/

const int N = 200000+5;
const int OFFSET = 2;

ll k;
int n,w;
int a[N+OFFSET], t[N+OFFSET];
set<ii> partly, full;

bool Insert(int pos, ll &Dur, ll &Ple, bool commit){
	ll new_Dur = Dur;
	if(partly.size() == w){
		ii F = *partly.begin();
		if(t[pos] >= F.first){
			int new_val = F.first;
			int previous_val = (F.first+1)/2;
			int insert_val = (t[pos]+1)/2;
			new_Dur += new_val - previous_val + insert_val;
			if(commit){
				partly.erase(F);
				full.insert(F);
				partly.insert(mp(t[pos],pos));
				Dur = new_Dur;
				Ple += a[pos];
			}
			return new_Dur <= k;
		}
		else{
			new_Dur += t[pos];
			if(commit){
				full.insert(mp(t[pos],pos));
				Dur = new_Dur;
				Ple += a[pos];
			}
			return new_Dur <= k;
		}
	}
	else{
		new_Dur += (t[pos]+1)/2;
		if(commit){
			partly.insert(mp(t[pos],pos));
			Dur = new_Dur;
			Ple += a[pos];
		}
		return new_Dur <= k;
	}
}

void TakeOff(int pos, ll &Dur, ll &Ple){
	if(partly.find(mp(t[pos],pos)) == partly.end()){
		// The one we erase is in full set
		full.erase(mp(t[pos],pos));
		Dur -= t[pos];
		Ple -= a[pos];
	}
	else{
		// The one we erase is in partly set
		partly.erase(mp(t[pos],pos));
		Dur -= (t[pos]+1)/2;
		Ple -= a[pos];
		while(partly.size() < w and full.size()){
			ii change = *full.rbegin();
			full.erase(change);
			Dur -= change.first;
			partly.insert(change);
			Dur += (change.first+1)/2;
		}
	}
}

int main(){
	ri2(n,w);
	rll(k);
	for(int i=0; i<n; i++){
		ri(a[i]);
	}
	for(int i=0; i<n; i++){
		ri(t[i]);
	}
	ll ans = 0;
	ll Dur = 0;
	ll Ple = 0;
	int r = 0;
	for(int l=0; l<n and r<n; l++){
		while(r < n and Insert(r,Dur,Ple,0)){
			bool dump = Insert(r++,Dur,Ple,1);
		}
		ans = max(ans,Ple);
		TakeOff(l,Dur,Ple);
	}
	cout << ans << endl;
	return 0;
}
