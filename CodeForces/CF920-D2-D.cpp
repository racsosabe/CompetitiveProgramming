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

const int N = 5000+5;

int n,k,v;
int a[N];
bool memo[N][N][3];
bool vis[N][N][3];
bool choice[N][N][3];
viii ans;

bool DP(int pos, int rem, bool valid){
	if(pos == n){
		return rem == v%k and valid;
	}
	if(vis[pos][rem][valid]) return memo[pos][rem][valid];
	bool can = false;
	if(DP(pos+1,add(rem,a[pos],k),1)){
		choice[pos][rem][valid] = 1;
		can = true;
	}
	else if(DP(pos+1,rem,valid)){
		choice[pos][rem][valid] = 0;
		can = true;
	}
	vis[pos][rem][valid] = true;
	return memo[pos][rem][valid] = can;
}

bool Rebuild(){
	if(v){
		// Take all that are needed to form the same remainder
		int rem = 0;
		bool valid = 0;
		vi used;
		for(int i=0; i<n; i++){
			if(choice[i][rem][valid]){
				rem = add(rem,a[i],k);
				used.pb(i);
				valid = true;
			}
		}
		// If used more than 1, put all in one tank
		if(used.size() > 1){
			for(int i=1; i<used.size(); i++){
				if(a[used[i]]) ans.pb(mp((a[used[i]]+k-1)/k,mp(used[i]+1,used[0]+1)));
				a[used[0]] += a[used[i]];
				a[used[i]] = 0;
			}
		}
		// Check if the tank used is equal, else
		// Take off or add on water
		if(a[used[0]] < v){
			// Add water, take a pivot tank (next one) and after
			// pouring water to it, add it to the main one
			int pivot = add(used[0],1,n);
			int needed = v - a[used[0]];
			priority_queue<ii> Q;
			for(int i=0; i<n; i++){
				if(i == used[0] or i == pivot) continue;
				if(a[i]) Q.push(mp(a[i],i));
			}
			while(a[pivot] < needed and !Q.empty()){
				ii Max = Q.top(); Q.pop();
				a[pivot] += Max.first;
				ans.pb(mp((Max.first+k-1)/k,mp(Max.second+1,pivot+1)));
			}
			if(a[pivot] < needed) return false;
			int times = needed / k;
			if(times) ans.pb(mp(times,mp(pivot+1,used[0]+1)));
		}
		else if(a[used[0]] > v){
			int times = abs(a[used[0]]-v)/k;
			if(times) ans.pb(mp(times,mp(used[0]+1,add(used[0],1,n)+1)));
		}
	}
	else{
		for(int i=0; i<n; i++){
			if(a[i]){
				ans.pb(mp((a[i]+k-1)/k,mp(i+1,add(i,1,n)+1)));
				break;
			}
		}
	}
	return ans.size();
}

int main(){
	ri3(n,k,v);
	int S = 0;
	for(int i=0; i<n; i++){
		ri(a[i]);
		S += a[i];
	}
	if(S < v){
		puts("NO");
		return 0;
	}
	for(int i=0; i<n; i++){
		if(a[i] == v){
			puts("YES");
			return 0;
		}
	}
	if(DP(0,0,0) or v == 0){
		if(Rebuild()){
			puts("YES");
			for(int i=0; i<ans.size(); i++){
				printf("%d %d %d\n",ans[i].first,ans[i].second.first,ans[i].second.second);
			}
		}
		else puts("NO");
	}
	else if(v%k==0){
		for(int i=1; i<n; i++){
			ans.pb(mp((a[i]+k-1)/k,mp(i+1,1)));
			a[0] += a[i];
			a[i] = 0;
		}
		ans.pb(mp(v/k,mp(1,2)));
		puts("YES");
		for(int i=0; i<ans.size(); i++){
			printf("%d %d %d\n",ans[i].first,ans[i].second.first,ans[i].second.second);
		}
	}
	else puts("NO");
	return 0;
}
