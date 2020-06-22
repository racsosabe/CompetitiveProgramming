#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cassert>
#include<utility>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
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

vector<int> s;
vector<int> group;

bool comp(int i, int j){
	return s[i] < s[j];
}

bool comp2(int i, int j){
	if(group[i] == group[j]) return i < j;
	return group[i] < group[j];
}

vector<int> suffix_array(int char_bound = -1) {
	int n = s.size();
	vector<int> a(n);
	if (n == 0) {
		return a;
	}
	if (char_bound != -1) {
		vector<int> aux(char_bound, 0);
		for (int i = 0; i < n; i++) {
			aux[s[i]]++;
		}
		int sum = 0;
		for (int i = 0; i < char_bound; i++) {
			int add = aux[i];
			aux[i] = sum;
			sum += add;
		}
		for (int i = 0; i < n; i++) {
			a[aux[s[i]]++] = i;
		}
	} else {
		for(int i=0; i<a.size(); i++) a[i] = i;
		sort(a.begin(), a.end(), comp);
	}
	vector<int> sorted_by_second(n);
	vector<int> ptr_group(n);
	vector<int> new_group(n);
	group.resize(n);
	group[a[0]] = 0;
	for (int i = 1; i < n; i++) {
		group[a[i]] = group[a[i - 1]] + (!(s[a[i]] == s[a[i - 1]]));
	}
	int step = 1;
	while (step < n) {
		int at = 0;
		for(int i = 0; i < n; i++){
			sorted_by_second[at++] = a[i] - step < 0? a[i] - step + n : a[i] - step;
		}
		for (int i = n - 1; i >= 0; i--) {
			ptr_group[group[a[i]]] = i;
		}
		for (int i = 0; i < n; i++) {
			int x = sorted_by_second[i];
			a[ptr_group[group[x]]++] = x;
		}
		new_group[a[0]] = 0;
		for (int i = 1; i < n; i++) {
			if (group[a[i]] != group[a[i - 1]]) {
				new_group[a[i]] = new_group[a[i - 1]] + 1;
			} else {
				int pre = (a[i - 1] + step >= n ? group[a[i - 1] + step - n] : group[a[i - 1] + step]);
				int cur = (a[i] + step >= n ? group[a[i] + step - n] : group[a[i] + step]);
				new_group[a[i]] = new_group[a[i - 1]] + (pre != cur);
			}
		}
		swap(group, new_group);
		step <<= 1;
	}
	sort(a.begin(),a.end(),comp2);
	return a;
}

vector<int> lcp_construction(vector<int> &a){
	int n = s.size();
	vector<int> rank(n, 0);
	for(int i=0; i<n; i++){
		rank[a[i]] = i;
	}
	int k = 0;
	vector<int> lcp(n-1,0);
	for(int i=0; i<n; i++){
		if(rank[i] == n-1){
			k = 0;
			continue;
		}
		int j = a[rank[i]+1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k += 1;
		lcp[rank[i]] = k;
		if(k > 0) k -= 1;
	}
	return lcp;
}

bool can(int len, vector<int> &lcp, vector<int> &sa){
	int leftmost = 1<<20;
	int rightmost = -1<<20;
	for(int i=0; i+1 < sa.size(); i++){
		if(lcp[i] >= len){
			leftmost = min(leftmost,sa[i+1]);
			rightmost = max(rightmost,sa[i+1]);
		}
		else{
			leftmost = rightmost = sa[i+1];
		}
		if(rightmost - leftmost >= len + 1) return true;
	}
	return false;
}

int n;

int main(){
	while(scanf("%d",&n) == 1 and n){
		vector<int> v(n);
		for(int i=0; i<n; i++){
			scanf("%d",&v[i]);
		}
		s.resize(n);
		s[n-1] = -1<<30;
		for(int i=0; i+1<n; i++){
			s[i] = v[i+1] - v[i] + 88;
		}
		vector<int> sa = suffix_array();
		vector<int> lcp = lcp_construction(sa);
		int lo = 0, hi = n;
		while(lo < hi){
			int mi = lo + (hi-lo+1)/2;
			if(can(mi,lcp,sa)) lo = mi;
			else hi = mi-1;
		}
		int ans;
		if(!can(lo,lcp,sa) or lo < 4) ans = 0;
		else ans = lo + 1;
		printf("%d\n",ans);
	}
	return 0;
}
