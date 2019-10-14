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

int n;
int want;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l,r)(rng);
}
/*
int Med3(int a, int b, int c){
	cout << a << " " << b << " " << c << endl;
	int x;
	cin >> x;
	return x;
}
*/
int solve(vi &L, vi &M, vi &R, int a, int b){
//	puts("NEW DIVISION:");
	if(L.size() < R.size()){
		swap(L,R);
		swap(a,b);
	}
//	for(int x:L){
//		cout << x << " ";
//	}
//	cout << " -- " << a << " -- ";
//	for(int x:M){
//		cout << x << " ";
//	}
//	cout << " -- " << b << " -- ";
//	for(int x:R){
//		cout << x << " ";
//	}
//	cout << endl;
	if(L.size() == want) return a;
	if(L.size() + M.size() + 1 == want) return b;
	if(L.size() > want){
//		puts("FIRST CASE");
		vector<int> L1;
		vector<int> M1;
		vector<int> R1;
		b = L[random(0,L.size()-1)];
		for(int i=0; i<L.size(); i++){
			int x = L[i];
			if(x == a or x == b) continue;
			int e = Med3(a,b,x);
			if(e == x) M1.emplace_back(x);
			else if(e == a) L1.emplace_back(x);
			else R1.emplace_back(x);
		}
		L.clear();
		M.clear();
		R.clear();
		return solve(L1,M1,R1,a,b);
	}
	else{
		vector<int> L1;
		vector<int> M1;
		vector<int> R1;
//		puts("SECOND CASE");
		if(L.size() + M.size() + 1 >= want){
//			puts("L + M");
			for(int i=0; i<M.size(); i++) L.emplace_back(M[i]);
			b = L[random(0,L.size()-1)];
			for(int i=0; i<L.size(); i++){
				int x = L[i];
				if(x == a or x == b) continue;
				int e = Med3(a,b,x);
				if(e == x) M1.emplace_back(x);
				else if(e == b) R1.emplace_back(x);
				else L1.emplace_back(x);
			}
			L.clear();
			M.clear();
			R.clear();
			return solve(L1,M1,R1,a,b);
		}
		else{
//			puts("R + M");
			for(int i=0; i<M.size(); i++) R.emplace_back(M[i]);
			a = R[random(0,R.size()-1)];
			for(int i=0; i<R.size(); i++){
				int x = R[i];
				if(x == a or x == b) continue;
				int e = Med3(a,b,x);
				if(e == x) M1.emplace_back(x);
				else if(e == a) L1.emplace_back(x);
				else R1.emplace_back(x);
			}
			L.clear();
			M.clear();
			R.clear();
			return solve(L1,M1,R1,a,b);
		}
	}
}

int Median(int n){
	if(n == 1) return 1;
	want = n / 2;
	int a = random(1,n);
	int b = random(1,n);
	while(a == b){
		b = random(1,n);
	}
	vector<int> L;
	vector<int> M;
	vector<int> R;
	for(int i=1; i<=n; i++){
		if(i == a or i == b) continue;
		int e = Med3(a,b,i);
		if(e == i) M.emplace_back(i);
		else if(e == a) L.emplace_back(i);
		else R.emplace_back(i);
	}
	return solve(L,M,R,a,b);
}
/*
int main(){
	int n;
	cin >> n;
	cout << Median(n) << endl;
	return 0;
}*/
