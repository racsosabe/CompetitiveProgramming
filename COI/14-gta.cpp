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

	- Ad-hoc problem.

	- Basically, according to editorial, we can just generate all the possible strings

	  with length at most 8 and get some equivalence classes where our relation

	  is "A can be transformed to B using valid movements".

	- Then, we can get the smallest string that belongs to each class (representative) and use it

	  to transform the original strings to get its final class. This can be

	  done by taking the first or last 5 characters of the string and replace it

	  with the representative until our final string has a length less than 5.

	- After that, just compare the classes to get the answer.

	- Complexity: O(4^len * len + m * log(4^len)), where len = 8 and m is the sum

	  of lengths of all the strings.
*/

const int N = 100+5;
const int MAX = 1<<16;
const string letters = "ATGC";

int n;
int C = 0;
int v[N];
set<string> vis;
vector<string> seeds;
string smallest[MAX];
map<string, int> comp;

int ord(char c){
	for(int i = 0; i < 4; i++){
		if(c == letters[i]) return i;
	}
	return -1;
}

void backtracking(int pos, string &s){
	if(pos == 8){
		seeds.emplace_back(s);
		return;
	}
	if(pos) seeds.emplace_back(s);
	for(int i = 0; i < 4; i++){
		s.push_back(letters[i]);
		backtracking(pos + 1, s);
		s.pop_back();
	}
}

void DFS(string s){
	comp[s] = C;
	vis.emplace(s);
	for(int i = 0; i + 1 < s.size(); i++){
		int pos1 = ord(s[i]);
		int pos2 = ord(s[i + 1]);
		if(pos2 == add(pos1, 2, 4)){
			string nxt = s.substr(0, i) + letters[add(pos1, 3, 4)] + s.substr(i + 2);
			if(!vis.count(nxt)) DFS(nxt);
		}
	}
	for(int i = 0; i < s.size(); i++){
		int pos = ord(s[i]);
		string nxt = s.substr(0, i) + letters[add(pos, 1, 4)] + letters[add(pos, 3, 4)] + s.substr(i + 1);
		if(nxt.size() <= 8 and !vis.count(nxt)) DFS(nxt);
	}
}

void getClasses(){
	sort(all(seeds), [&] (string a, string b){
		return a.size() < b.size();		
	});
	for(auto x : seeds){
		if(vis.count(x)) continue;
		DFS(x);
		C += 1;
	}
	for(int i = 0; i < seeds.size(); i++){
		int cc = comp[seeds[i]];
		if(smallest[cc].size()) continue;
		smallest[cc] = seeds[i];
	}
}

bool equiv(int i, int j){
	return v[i] == v[j];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string s = "";
	backtracking(0, s);
	getClasses();
	cin >> n;
	for(int i = 1; i <= n; i++){
		string s;
		cin >> s;
		while(s.size() > 4){
			int len = s.size();
			string nxt = smallest[comp[s.substr(len - 5)]];
			for(int i = 0; i < 5; i++) s.pop_back();
			s += nxt;
		}
		v[i] = comp[s];
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cout << (equiv(i, j)? '1':'0');
		}
		cout << '\n';
	}
	return 0;
}
