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
		- Important Expectation & Probability problem.

		- Let's say that we already have k different coupons, so

		  the probability of getting a new one is (n-k)/n, which

		  means that the expectancy is n/(n-k), so we get the sum

		  for each case (k=1,..,n) and add all of them

		- S = \sum\limits_{i=1}^{n}\frac{n}{i} = n\sum\limits_{i=1}^{n}\frac{1}{i}


*/

class Fraction{
	ll num;
	ll den;
	public:
	Fraction(ll _num, ll _den){
		ll mcd = gcd(_num,_den);
		_num /= mcd;
		_den /= mcd;
		num = _num;
		den = _den;
	}
	void sum(Fraction b){
		ll new_num = num*b.getDen() + den*b.getNum();
		ll new_den = den*b.getDen();
		ll mcd = gcd(new_num,new_den);
		new_num /= mcd;
		new_den /= mcd;
		num = new_num;
		den = new_den;
	}
	void mult(Fraction b){
		ll new_num = num*b.getNum();
		ll new_den = den*b.getDen();
		ll mcd = gcd(new_num,new_den);
		new_num /= mcd;
		new_den /= mcd;
		num = new_num;
		den = new_den;
	}
	ll getNum(){ return num;}
	ll getDen(){ return den;}
	void Print(){
		ll integer = num/den;
		ll remainder = num % den;
		if(remainder){
			int len_n = 0;
			ll carry = den;
			while(carry){
				carry /= 10;
				len_n++;
			}
			int len_i = 0;
			carry = integer;
			while(carry){
				carry /= 10;
				len_i++;
			}
			for(int i=0; i<=len_i; i++) putchar(' ');
			printf("%lld\n",remainder);
			printf("%lld ",integer);
			for(int i=0; i<len_n; i++) putchar('-');
			puts("");
			for(int i=0; i<=len_i; i++) putchar(' ');
			printf("%lld\n",den);

		}
		else{
			printf("%lld\n",integer);
		}
	}
};

int n;

int main(){
	while(ri(n)==1){
		Fraction S(0,1);
		for(ll i=1; i<=n; i++){
			S.sum(Fraction(1LL,i));
		}
		S.mult(Fraction(n,1));
		S.Print();
	}
	return 0;
}
