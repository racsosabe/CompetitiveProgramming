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

		- Good DP & Trie problem.

		- First, sort lexicographically the words and relate them to a

		  "lex id" according to it.

		- Since we want suffixes, reverse the strings when inserting them
		  into the Trie

		- Compute the first and second minimum "lex ids", because all

		  the words are different so one of them may not match with query

		- Use DP to make the former query in O(1)

		- Save all the nodes that match with query and go from highest to
		  lowest match: take the first solution that doesn't match with

		  query, this is O(length of query).

		- Complexity: O(nMlogn + qM). M = Max length of words.
*/

const int N = 250000;
const int E = 26;
const int M = 30;

int nodes = 1;
int word_id[N*M+5];
int min_id[N*M+5];
int sec_id[N*M+5];
int Trie[N*M+5][E+5];
vector<string> words;

void insert(string s, int id){ // Insert the word s with "lex id" = id
	int p = 0;
	int last = 0;
	for(int i=0; i<s.size(); i++){
		if(Trie[p][s[i]-'a'] == 0){
			Trie[p][s[i]-'a'] = nodes++;
		}
		last = p;
		p = Trie[p][s[i]-'a'];
	}
	word_id[p] = id;
}

int getMin(int u){ // Gets the minimum lex child for node u and computes 2nd min
	if(min_id[u] != -1) return min_id[u];
	int ans = INT_MAX;
	int Fmin = INT_MAX;
	int Smin = INT_MAX;
	for(int i=0; i<26; i++){
		if(Trie[u][i]){
			int cand = getMin(Trie[u][i]);
			if(cand < Smin) Smin = cand;
			if(Smin < Fmin) swap(Fmin,Smin);
		}
	}
	if(word_id[u] != -1){
		int cand = word_id[u];
		if(cand < Smin){
			Smin = cand;
		}
		if(Smin < Fmin) swap(Fmin,Smin);
	}
	sec_id[u] = Smin;
	return min_id[u] = Fmin;
}

int solve(string x){ // Answers the query with the id of the word
	int p = 0;
	vector<int> ids;
	for(int i=0; i<x.size(); i++){
		if(Trie[p][x[i]-'a']){
			ids.pb(p);
			p = Trie[p][x[i]-'a'];
		}
		else break;
	}
	int ans = INT_MAX;
	reverse(all(x));
	int id = min_id[p];
	if((id < 0 or id >= int(words.size())) or words[id] == x){
		if((sec_id[p] < 0 or sec_id[p] >= words.size()) or words[sec_id[p]] == x){
			for(int i=ids.size()-1; i>=0 and ans==INT_MAX; i--){
				p = ids[i];
				if(words[min_id[p]] != x) ans = min_id[p];
				else if((sec_id[p] >= 0 and sec_id[p] < words.size())){
					ans = sec_id[p];
				}
			}
		}
		else{
			ans = sec_id[p];
		}
	}
	else{
		ans = id;
	}
	return ans;
}

int main(){
	string s;
	while(getline(cin,s) and s!=""){
		words.pb(s);
	}
	memset(word_id,-1,sizeof word_id);
	memset(min_id,-1,sizeof min_id);
	memset(sec_id,-1,sizeof sec_id);
	sort(all(words));
	for(int i=0; i<words.size(); i++){
		string s = words[i];
		reverse(all(s));
		insert(s,i);
	}
	getMin(0);
	while(getline(cin,s)){
		reverse(all(s));
		int id = words.size() > 1?solve(s):0;
		string ans = words[id];
		printf("%s\n",ans.c_str());
	}
	return 0;
}
