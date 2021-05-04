#include<bits/stdc++.h>
using namespace::std;

/*
	Grand Prix of China - Problem A "Namomo Subsequence"	

	Author: Racso Galvan

	Idea:

	- Notice that according to the condition, we need all the subsequence of the form 123434

	  given that 1, 2, 3 and 4 are different characters.

	- Let's separate the wanted subsequence in 12 + 3434, which means that we can

	  first count the number of subsequences 3434 and then count the number of 

	  subsequences 12 that are to the left.

	- To avoid double counting, we can set memo[i][c] as the number of subsequences

	  of s[i:] with the form s[i] + c + s[i] + c. This can be computed in O(n * E)

	  where E is the size of the alphabet.

	- After that, we can just process all the subsequences with the form xy with

	  x != y.

	- To compute the valid sequences, use Inclusion-Exclusion Principle, which will be

	  adding all the valid subsequences xy (x != y) and then taking off the 

	  ones that have x = s[i] or y = s[i] and the ones having x = c or y = c

	  to finally add again the subsequences of the form x = s[i], y = c and x = c, y = s[i].

	- Complexity: O(nE)

*/

const string pattern = "123434";
const int MOD = 998244353;
const int N = 1000000 + 5;
const int E = 62;

int n;
string s;
int a[N];
int F[E];
int U[E];
int Q[E][E];
int memo[N][E];
int C[E][E][E];

int id(char c){
	if(isdigit(c)) return c - '0';
	if(islower(c)) return 10 + c - 'a';
	return 36 + c - 'A';
}

int solve(){
	for(int i = 0; i < n; i++) a[i] = id(s[i]);
	for(int i = n - 1; i >= 0; i--){
		int x = a[i];
		for(int c = 0; c < E; c++){
			if(c == x) continue;
			memo[i][c] += C[c][x][c];
			if(memo[i][c] >= MOD) memo[i][c] -= MOD;
			C[x][c][x] += Q[c][x];
			if(C[x][c][x] >= MOD) C[x][c][x] -= MOD;
			Q[x][c] += F[c];
			if(Q[x][c] >= MOD) Q[x][c] -= MOD;
		}
		F[x] += 1;
	}
	for(int i = 0; i < E; i++){
		F[i] = 0;
		for(int j = 0; j < E; j++) Q[i][j] = 0;
	}
	int total_pairs = 0;
	int ans = 0;
	for(int i = 0; i < n; i++){
		int x = a[i];
		for(int c = 0; c < E; c++){
			if(c == x) continue;
			if(memo[i][c] == 0) continue;
			int valid = total_pairs;
			valid += MOD - U[x];
			if(valid >= MOD) valid -= MOD;
			valid += MOD - U[c];
			if(valid >= MOD) valid -= MOD;
			valid += Q[c][x];
			if(valid >= MOD) valid -= MOD;
			valid += Q[x][c];
			if(valid >= MOD) valid -= MOD;
			ans += (1ll * memo[i][c] * valid) % MOD;
			if(ans >= MOD) ans -= MOD;
		}
		for(int c = 0; c < E; c++){
			if(x == c) continue;
			Q[c][x] += F[c];
			total_pairs += F[c];
			if(Q[c][x] >= MOD) Q[c][x] -= MOD;
			if(total_pairs >= MOD) total_pairs -= MOD;
			U[c] += F[c];
			if(U[c] >= MOD) U[c] -= MOD;
			U[x] += F[c];
			if(U[x] >= MOD) U[x] -= MOD;
		}
		F[x] += 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin >> s;
	n = s.size();
	cout << solve() << endl;
	return 0;
}
