#include<iostream>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
#include<map>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<stack>
#include<cstring>
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
		- Basic 2D-Coordinate Compression Problem.

		- Let's say that we divide the plane in different cells so that

		  for each cell, we can have one point of any of the rectangles

		  to represent it.

		- Then, we'll only need to 'color' the matrix like 2D Range Sum DP
		  to distinguish between the ones that are used and the unused ones.

		- We can do the division by making a 1D coordinate compresion for the
		  Xs and Ys and using the product of those to set a matrix.

		- Once we have done the coloring of the matrix, just check for each
		  colored cell, if any neighbor is NOT colored, so we'll need to add
		  that side to the final answer.

		- Complexity: O(n^2 + MAX) = O(n^2).
*/

const int N = 5000+5;
const int M = 30000+5;
const int A = 10005+5;

int n;
int ac[N<<2][N<<2];
int x[N<<2], y[N<<2];
int posx[M], posy[M];
int valx[M], valy[M];
int rx[] = {0,0,1,1};
int ry[] = {1,1,0,0};
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
bool usedX[M], usedY[M];

int main(){
	ri(n);
	int p = 0;
	int x1,x2,y1,y2;
	usedX[0] = usedY[0] = true;
	usedX[M-1] = usedY[M-1] = true;
	for(int i=0; i<n; i++){
		ri2(x1,y1);
		ri2(x2,y2);
		x1 += A;
		y1 += A;
		x2 += A;
		y2 += A;
		usedX[x1] = true;
		usedY[y1] = true;
		usedX[x2] = true;
		usedY[y2] = true;
		x[p] = x1;
		y[p++] = y1;
		x[p] = x1;
		y[p++] = y2;
		x[p] = x2;
		y[p++] = y2;
		x[p] = x2;
		y[p++] = y1;
	}
	int px = 0, py = 0;
	// Coordinate Compression for X and Y
	for(int i=0; i<M; i++){
		if(usedX[i]){
			valx[px] = i;
			posx[i] = px++;
		}
		if(usedY[i]){
			valy[py] = i;
			posy[i] = py++;
		}
	}
	// Coloring the matrix
	for(int i=0; i<p; i++){
		if(i&1){
			ac[posx[x[i]]][posy[y[i]]]--;
		}
		else{
			ac[posx[x[i]]][posy[y[i]]]++;
		}
	}
	for(int i=0; i<px; i++){
		for(int j=0; j<py; j++){
			if(i > 0) ac[i][j] += ac[i-1][j];
			if(j > 0) ac[i][j] += ac[i][j-1];
			if(i > 0 and j > 0) ac[i][j] -= ac[i-1][j-1];
		}
	}
	// Computing answer
	int ans = 0;
	for(int i=0; i<px; i++){
		for(int j=0; j<py; j++){
			if(ac[i][j] > 0){
				for(int k=0; k<4; k++){
					int vx = i + dx[k];
					int vy = j + dy[k];
					int refx = i + rx[k];
					int refy = j + ry[k];
					if(ac[vx][vy] == 0){
						ans += valx[refx] - valx[i] + valy[refy] - valy[j];
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
