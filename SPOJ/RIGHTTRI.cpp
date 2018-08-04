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
		- Interesting Geometry and Two Pointers problem.

		- First, let's suppose that we have a center point O, so we only

		  need to count how many pair of points (a,b) from the set S/{O}

		  exist such that:

		  (a-O).(b-O) = 0, where . is dot product.

		- So, we are going to fix a center point, then order the rest of points 

		  clockwise or counterclockwise (we chose counterclockwise for this sol)

		  So, we only need to use two pointers to avoid cuadratic complexity.

		  Also, we can set a counter for each "repeated" vectors (for two parallel

		  vectors the answer is the same).

		  Now, to avoid double counting, we can say that the angle must be

		  0Â° < theta < 80Â, so we need that

		  dot(v1,v2) = 0 and cross(v1,v2) < 0 to count v1,v2 as a right angle.

*/

const int N = 1500+5;

class Punto{
	int x;
	int y;
	public:
	Punto(){
		x = y = 0;
	}
	Punto(int _x, int _y){
		x = _x;
		y = _y;
	}
	Punto(const Punto &p){
		x = p.x;
		y = p.y;
	}
	int getX(){ return x;}
	int getY(){ return y;}
	Punto operator + (const Punto &p) const {
		return Punto(x+p.x,y+p.y);
	}
	Punto operator - (const Punto &p) const {
		return Punto(x-p.x,y-p.y);
	}
};

int n;
ll ans;
Punto O;
Punto v[N];
Punto rest[N];

ll dot(Punto &a, Punto &b){
	return 1LL*a.getX()*b.getX() + 1LL*a.getY()*b.getY();
}

ll cross(Punto &a, Punto &b){
	return 1LL*a.getX()*b.getY() - 1LL*a.getY()*b.getX();
}

bool ccwcomparison(Punto &a, Punto &b){
	int x1 = a.getX();
	int y1 = a.getY();
	int x2 = b.getX();
	int y2 = b.getY();
	if(x1 >= O.getX() and x2 < O.getX()) return true;
	if(x1 < O.getX() and x2 >= O.getX()) return false;
	if(x1 - O.getX() == 0 and x2 - O.getX() == 0){
		if(y1 - O.getY() >= 0 or y2 - O.getY() >= 0) return y1 > y2;

		return y2 > y1;
	}
	Punto c = a-O, d = b-O;
	return cross(c,d) < 0;
}

void Print(Punto &p){
	cout << p.getX() << " " << p.getY() << endl;
}

void solve(){
	int k = 1;
	int counter = 0;
	int last = 0;
	for(int j=0; j<n-1; j++){
		Punto act = rest[j];
		if(k%(n-1)==j) k++;
		while(k%(n-1)!=j){
			Punto v1 = act-O;
			Punto v2 = rest[k%(n-1)]-O;
			if(dot(v1,v2) <= 0 or cross(v1,v2) > 0) break;
			k++;
		}
		Punto v1 = act-O, v2 = rest[k%(n-1)]-O;
		if(j){
			Punto v3 = rest[j-1] - O;
			if(cross(v1,v3)==0 and dot(v1,v3) > 0){
				ans += counter;
			}
			else{
				counter = 0;
				while(k%(n-1)!=j){
					Punto v1 = act-O;
					Punto v2 = rest[k%(n-1)]-O;
					if(dot(v1,v2)!=0 or cross(v1,v2) >= 0) break;
					counter++;
					k++;
				}
				ans += counter;
			}
		}
		else{
			counter = 0;
			while(k%(n-1)!=j){
				Punto v1 = act-O;
				Punto v2 = rest[k%(n-1)]-O;
				if(dot(v1,v2)!=0 or cross(v1,v2)>=0) break;
				counter++;
				k++;
			}
			ans += counter;
		}
	}
}

int main(){
	ri(n);
	int x,y;
	for(int i=0; i<n; i++){
		ri2(x,y);
		v[i] = Punto(x,y);
	}
	ans = 0LL;
	int n2 = n-1;
	for(int i=0; i<n; i++){
		O = v[i];
		int p = 0;
		for(int j=0; j<n; j++){
			if(i == j) continue;
			rest[p++] = v[j];
		}
		sort(rest,rest+n2,ccwcomparison);
		solve();
	}
	printf("%lld\n",ans);
	return 0;
}
