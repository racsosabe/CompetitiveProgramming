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
		- Good DP & Bitmaks & Game Theory problem.

		- We can simulate a table as a ternary mask, so we have at most

		  3^16 - 1 different states.

		  We use 0 = free, 1 = 'x' and 2 = 'o'.

		  Now, let's say that DP(turn,bitmask) gives us the winner of

		  table "bitmask" when player "turn" has made the best choice 

		  possible.

		  Then we just need to brute force over all the possible next moves
			
		  and get the forced win one that appears first.

		- Note: The winners are decided like this:

			- Current Player wins: If any move makes him win.

			- Draw: If there's no move to win but there is at least one to draw

			- Current Player loses: There's no move to win nor draw

		  It's a simple variation from the classical winning and losing moves
		- Complexity: O(3^{size of table} + T).

		  Where T is the number of test cases and size of table is 16.

		- Observation: Since we are using the same table, then 

		  we use the same states, therefore there's no need to memset them

		  to unvisited each case.
*/

const int N = 43046721+5;

int e3[20];
bool vis[3][N];
int memo[3][N];
vii wins[12];

bool full(int bitmask){
	for(int i=0; i<16; i++){
		int val = (bitmask / e3[i])%3;
		if(val == 0) return false;
	}
	return true;
}

int win(int bitmask){
	for(int i=0; i<10; i++){
		int x0 = wins[i][0].first;
		int y0 = wins[i][0].second;
		int p0 = (x0<<2) + y0;
		int val0 = (bitmask / e3[p0])%3;
		bool can = val0 > 0;
		for(int j=1; j<4 and can; j++){
			int x1 = wins[i][j].first;
			int y1 = wins[i][j].second;
			int p1 = (x1<<2) + y1;
			int val1 = (bitmask/e3[p1])%3;
			if(val0 != val1){
				can = false;
			}
		}
		if(can) return val0;
	}
	return 0;
}

int DP(int turn, int bitmask){
	int w = win(bitmask);
	if(w) return w;
	if(full(bitmask)) return 0;
	if(vis[turn][bitmask]) return memo[turn][bitmask];
	bool draw = false;
	vis[turn][bitmask] = true;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			int p = (i<<2)+j;
			int val = (bitmask/e3[p])%3;
			if(val == 0){
				int winner_from_move = DP(3-turn,bitmask+e3[p]*turn);
				if(winner_from_move == turn){
					return memo[turn][bitmask] = turn;
				}
				else if(winner_from_move == 0){
					draw = true;
				}
			}
		}
	}
	return memo[turn][bitmask] = draw?0:3-turn;
}

void init(){
	e3[0] = 1;
	for(int i=1; i<=16; i++) e3[i] = 3*e3[i-1];
	int p = 0;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			wins[p].pb(mp(i,j));
		}
		p++;
	}
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			wins[p].pb(mp(j,i));
		}
		p++;
	}
	for(int i=0; i<4; i++){
		wins[p].pb(mp(i,i));
	}
	p++;
	for(int i=0; i<4; i++){
		wins[p].pb(mp(i,3-i));
	}
}

int main(){
	init();
	char x;
	while(x = getchar()){
		if(x == '$') break;
		getchar();
		int bitmask = 0;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				x = getchar();
				int p = (i<<2) + j;
				if(x == 'x') bitmask += e3[p];
				else if(x == 'o') bitmask += e3[p]<<1;
			}
			getchar();
		}
		bool can = false;
		int a,b;
		for(int i=0; i<4 and !can; i++){
			for(int j=0; j<4 and !can; j++){
				int p = (i<<2) + j;
				int val = (bitmask / e3[p])%3;
				if(val == 0){
					int winner = DP(2,bitmask+e3[p]);
					if(winner == 1){
						can = true;
						a = i;
						b = j;
					}
				}
			}
		}
		if(can){
			printf("(%d,%d)\n",a,b);
		}
		else puts("#####");
	}
	return 0;
}
