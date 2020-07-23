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

int add(int a, int b, int m = MOD){
	return (a + b) % m;
}

int mul(ll a, ll b, int m = MOD){
	return (a * b) % m;
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

struct node{
	int M[3][3];
	node(){ memset(M, 0, sizeof M);};
	node(char x){
		memset(M, 0, sizeof M);
		if(x == 'S' or x == 'D'){
			M[0][1] = 1;
			M[1][1] = 1;
		}
		else if(x == 'H'){
			M[0][0] = 1;
			M[1][0] = 1;
		}
		else if(x == 'A' or x == 'E' or x == 'I' or x == 'O' or x == 'U'){
			M[0][1] = M[1][0] = 1;
		}
		else if(x == '?'){
			M[0][1] = M[1][0] = 5;
			M[0][1] += 2;
			M[1][1] += 2;
			M[0][0] += 1;
			M[1][0] += 1;
			M[0][0] += 18;
			M[1][1] += 18;
		}
		else{
			M[0][0] = M[1][1] = 1;
		}
	}
};	

const int N = 200000+5;

int n;
int q;
node NIL;
char s[N];
node st[4 * N];

node merge(node a, node b){
	node q;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			q.M[i][j] = 0;
			for(int k = 0; k < 2; k++){
				q.M[i][j] = add(q.M[i][j], mul(a.M[i][k], b.M[k][j]));
			}
		}
	}
	return q;
}

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = node(s[l]);
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = merge(st[2 * pos], st[2 * pos + 1]);
}

void update(int x, char c, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = node(c);
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, c, 2*pos, l, mi);
	else update(x, c, 2*pos+1, mi+1, r);
	st[pos] = merge(st[2*pos], st[2*pos+1]);
}

int main(){
	ri2(n, q);
	scanf("%s", s + 1);
	build();
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			NIL.M[i][j] = i == j;
		}
	}
	printf("%d\n", st[1].M[0][0]);
	int l;
	char c;
	while(q--){
		ri(l);
		c = getchar();
		while(c == ' ') c = getchar();
		update(l, c);
		printf("%d\n", st[1].M[0][0]);
	}
	return 0;
}
