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
		- Easy Math problem.

		- Just notice that we can have both chocolates as N1 = a1*b1 and N2=a2*b2

		  So, can say that:

		  N1 = 2^m1*3^n1*P

		  N2 = 2^m2*3^n2*Q

		  Since a 3 factor can be transformed only to a 2 factor, we need
		  that P = Q to work correctly, else the answer is -1.

		- Now, as 3 factors can convert to 2 factors, we first transform the
		  3's that are not needed, thus max(n1,n2) - min(n1,n2) minutes are
		  needed and the same amount of 2's will be added to the respective quantity.

		  After it, we need to take off 2's, by taking max(m1',m2') - min(m1',m2')

		  where m1' and m2' are the exponents of 2 after the transformation of 3's.

		- Complexity: O(logM^2), where M is the maximum value of a dimension.

*/

ll a1,a2,b1,b2;

int main(){
	rll2(a1,b1);
	rll2(a2,b2);
	ll P1 = a1*b1, P2 = a2*b2;
	int dos1 = 0, tres1 = 0, dos2 = 0, tres2 = 0;
	while(!(P1&1)){
		P1 >>= 1;
		dos1++;
	}
	while(P1%3==0){
		P1 /= 3;
		tres1++;
	}
	while(!(P2&1)){
		P2 >>= 1;
		dos2++;
	}
	while(P2%3==0){
		P2 /= 3;
		tres2++;
	}
	if(P1 != P2) puts("-1");
	else{
		int tres = min(tres1,tres2);
		int take3 = max(tres1,tres2) - tres;
		int minutes = take3;
		if(tres1 < tres2){
			dos2+=take3;
			while(take3 > 0 and a2%3==0){
				a2 /= 3;
				a2 <<= 1;
				take3--;
			}
			while(take3 > 0 and b2%3==0){
				b2 /= 3;
				b2 <<= 1;
				take3--;
			}
		}
		else{
			dos1+=take3;
			while(take3 > 0 and a1%3==0){
				a1 /= 3;
				a1 <<= 1;
				take3--;
			}
			while(take3 > 0 and b1%3==0){
				b1 /= 3;
				b1 <<= 1;
				take3--;
			}
		}
		int dos = min(dos1,dos2);
		int take2 = max(dos1,dos2) - dos;
		minutes += take2;
		if(dos1 < dos2){
			while(take2 > 0 and a2%2==0){
				a2 >>= 1;
				take2--;
			}
			while(take2 > 0 and b2%2==0){
				b2 >>= 1;
				take2--;
			}
		}
		else{
			while(take2 > 0 and a1%2==0){
				a1 >>= 1;
				take2--;
			}
			while(take2 > 0 and b1%2==0){
				b1 >>= 1;
				take2--;
			}
		}
		printf("%d\n%lld %lld\n%lld %lld\n",minutes,a1,b1,a2,b2);
	}
	return 0;
}
