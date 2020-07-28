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

/*
	Author: Racso Galvan

	Idea:

	- Backtracking problem. Explanation based on official editorial.

	- It's pretty hard to figure out a solution by inserting the elements from first
	
	  to last. Therefore we will try to insert them from last to first.

	- When we are adding the items from last to first, we will need the state of

	  the depot using the previous inserted elements, thus we will need to be able

	  to "undo" insert operations from a given state.

	- Consider that the last item added was X, then, according to the process,

	  this value might have:

	  1) Be the last in the first row.

	  2) Pushed a value Y > X (the first one that holds) from the first row to the 2nd one and took its place.

	  The second event triggers another process with similar structure but starting

	  in the second row.

	  It's easy to notice that this process ends in a 1st type event for some value

	  in some row. This helps us to think that the last inserted element is related

	  with a last-in-row value.

	- Due to the previous observation, we can pick every last-in-row element and

	  try to check if there was a possible value whose insertion would push that

	  last-in-row value to its current position. We can't do this if the row

	  has only 1 element and it's not the last one (since it would disconnect
	  
	  the state).

	- Let's consider the process and event types for just one step:

	  We have picked a value X which is the last in its row, then, we have two cases:

	  1) It's in the first row, in which case we just need to remove it directly

	  2) It's not in the first row, so it must exist a value Y that has pushed

	     it to this row and, for instance, we know that in that step the value

	     X was the first one that was greater than Y in that row. 

	     Thus, the value Y is the greatest in the previous row that is less than

	     X, so we can just use a binary search to find it.

	     In case the value Y doesn't exist, this value couldn't be inserted 

	     in this position from last to first.

	- If there is a valid element in the first row, then add it to the current

	  removed elements and commit the changes into the current depot state.

	- As an optimization, when we are left with one row, we can just add the

	  elements in reversed order directly and that will be the answer for that

	  state.

	- Complexity: O(ans * r^2 * logn), where ans is the number of solutions.

	  According to the editorial, it's bounded by O(n^2).
*/

int n;
int r;
vector<vi> target;

int remove(int x, int y, vector<vi> &cur){
	int val = cur[x][y];
	for(int i = x; i > 0; i--){
		int lo = 0, hi = cur[i - 1].size() - 1;
		while(lo < hi){
			int mi = lo + (hi - lo + 1) / 2;
			if(cur[i - 1][mi] < val) lo = mi;
			else hi = mi-1;
		}
		if(cur[i - 1][lo] > val) return 0;
		val = cur[i - 1][lo];
	}
	int res = val;
	val = cur[x][y];
	for(int i = x; i > 0; i--){
		int lo = 0, hi = cur[i - 1].size() - 1;
		while(lo < hi){
			int mi = lo + (hi - lo + 1) / 2;
			if(cur[i - 1][mi] < val) lo = mi;
			else hi = mi-1;
		}
		swap(val, cur[i - 1][lo]);
	}
	cur[x].pop_back();
	if(cur[x].empty()) cur.pop_back();
	return res;
}

void backtracking(vector<vi> &cur, vi &perm){
	if(perm.size() == n){
		for(int i = n - 1; i >= 0; i--){
			printf("%d%c", perm[i], " \n"[i == 0]);
		}
		return;
	}
	if(cur.size() == 1){
		for(int i = cur[0].size() - 1; i >= 0; i--){
			perm.emplace_back(cur[0][i]);
		}
		backtracking(cur, perm);
		for(int i = cur[0].size() - 1; i >= 0; i--){
			perm.pop_back();
		}
	}
	else{
		for(int i = 0; i < cur.size(); i++){
			if(cur[i].size() == 1 and i + 1 != cur.size()) continue;
			vector<vi> temp(cur);
			int toRemove = remove(i, cur[i].size() - 1, cur);
			if(toRemove){
				perm.emplace_back(toRemove);
				backtracking(cur, perm);
				perm.pop_back();
			}
			cur = temp;
		}
	}
}

void solve(){
	vector<int> perm;
	vector< vector<int> > cur = target;
	backtracking(cur, perm);
}

int main(){
	ri(r);
	target.resize(r);
	for(int i = 0; i < r; i++){
		int q;
		ri(q);
		n += q;
		target[i].resize(q);
		for(int j = 0; j < q; j++){
			ri(target[i][j]);
		}
	}
	solve();
	return 0;
}
