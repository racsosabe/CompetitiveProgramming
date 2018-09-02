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
		- Greedy problem.

		- First, notice that the first player always takes 1s from left to minimize
		  the final value, and the second player always takes 0s from left to maximize
		  it.

		- That said, we only need to check which values will be assigned from left
		  and thus we can get the final value of the current event.

		  But if we do that for every possible distribution we'll get a O(n^2)
		  and a TLE.

		- Optimization's observation: To get a "11" or "00" we only need that
		  Q[1] >= Q[0]+2 or viceversa respectively, so all these cases don't
		  need to be checked.

		  With that said, we see that the only distributions we'll have to check
		  are the ones like (x,x+d) where -1 <= d <= 1, so at most we'll

		  simulate only 5 cases. We can consider this in the naive brute force
		  solution or handle it by cases.

		- Complexity: O(n), where n is the length of the string.
*/

int n;
int unknown = 0;
int q[2];
string s;
set<string> S;

string tryThis(int left, int q1){
	// Tries to set as 'left' the first q1
	// '?' positions in the new string and
	// gets the final value for this case
	//
	// NOTE: If there are not enough '?'
	// it just ignores the rest.
	
	queue<int> Q[2];
	string carry = s;
	for(int i=0; i<n; i++){
		if(s[i] == '?'){
			if(q1){
				carry[i] = left + '0';
				q1--;
			}
			else carry[i] = 1 - left + '0';
		}
		Q[carry[i]-'0'].push(i);
	}
	int turn = 1;
	while(Q[0].size() + Q[1].size() > 2){
		if(!Q[turn].empty()){
			Q[turn].pop();
		}
		else{
			Q[1^turn].pop();
		}
		turn ^= 1;
	}
	vector<ii> pos;
	for(int i=0; i<2; i++){
		while(!Q[i].empty()){
			pos.pb(mp(Q[i].front(),i));
			Q[i].pop();
		}
	}
	sort(all(pos));
	string ans = "";
	ans += char(pos[0].second + '0');
	ans += char(pos[1].second + '0');
	return ans;
}

int main(){
	cin >> s;
	n = s.size();
	for(int i=0; i<n; i++){
		if(s[i] == '?') unknown++;
		else q[s[i]-'0']++;
	}
	for(int i=0; i<2; i++){
		if(q[i] + unknown >= q[1^i] + 2){
			string carry = "";
			carry += char(i+'0');
			carry += char(i+'0');
			S.insert(carry);
		}
	}
	if(n&1){
		int parts[2] = {n/2, (n+1)/2};
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				if(q[i] <= parts[j]){
					string carry = tryThis(i,parts[j]-q[i]);
					S.insert(carry);
				}
			}
		}
	}
	else{
		int parts[2] = {n/2, n/2};	
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				if(q[i] <= parts[j]){
					string carry = tryThis(i,parts[j]-q[i]);
					S.insert(carry);
				}
			}
		}
	}
	for(set<string>::iterator it=S.begin(); it!=S.end(); it++){
		s = *it;
		printf("%s\n",s.c_str());
	}
	return 0;
}
