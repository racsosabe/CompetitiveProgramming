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

const int N = 1000000+5;

int n;
int r,c;
int len[N];
vector<string> v;

int getMax(multiset<int> &S){
	if(S.empty()) return 0;
	multiset<int>::iterator it = S.end();
	it--;
	return *it;
}

int main(){
	ri3(n,r,c);
	string s;
	for(int i=0; i<n; i++){
		cin >> s;
		v.pb(s);
		len[i] = s.size();
	}
	multiset<int> S;
	int L = 0, R = 0;
	int left = 0, right = 0;
	int ans = 0;
	int sum = 0;
	while(right < n){
		while(left < right and (getMax(S) > c or sum - r > r*c)){
			S.erase(S.find(len[left]));
			sum -= len[left]+1;
			left++;
		}
		int current_line = 0;
		int lines = 0;
		for(int k=left; k<=right; k++){

		}
		while(right < n and getMax(S) <= c and sum + len[right]+1 - r <= r*c and lines <= r){
			if(len[right] > c){
				S.insert(len[right]);
				break;
			}
			sum += len[right]+1;
			S.insert(len[right]);
			right++;
		}
		int act = right-left;
		if(ans < act){
			ans = act;
			L = left;
			R = right-1;
		}
		if(right < n){
			if(len[right] > c){
				sum = 0;
				S.clear();
				right++;
				left = right;
			}
			else{
				sum += len[right]+1;
				S.insert(len[right]);
				right++;
			}
		}
	}
	

	if(getMax(S) <= c and sum-r <= c*r){
		int act = right-left;
		if(ans < act){
			ans = act;
			L = left;
			R = right-1;
		}
	}
	if(ans == 0) return 0;
	int line = 0;
	int pos = L;
	for(int i=0; i<r; i++){
		if(pos <= R){
			printf("%s",v[pos].c_str());
			line += len[pos++];
		}
		while(pos <= R and line+len[pos]+1 <= c){
			printf(" %s",v[pos].c_str());
			line += len[pos++]+1;
		}
		if(line) puts("");
		line = 0;
	}
	return 0;
}
