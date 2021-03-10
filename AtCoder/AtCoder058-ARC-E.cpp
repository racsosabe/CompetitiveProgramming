#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Aho-Corasick & DP problem

	- Compute the complement of the answer: The sequences that don't have XYZ in them

	- Thus, we can just hardcode all the sequences that shouldn't be inside our

	  answer.

	- Then, it reduces to a classic Aho-Corasick problem: Number of sequences

	  that don't contain any pattern given.

	- Complexity: O(n * nodes * E), where nodes is the sum of lengths of the forbidden

	  sequences, which is bounded by 34000.

*/

const int MOD = 1000000000 + 7;
const int SUML = 34000 + 5;
const int N = 40 + 5;
const int E = 10;

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = (1ll * a * r) % MOD;
		a = (1ll * a * a) % MOD;
		b >>= 1;
	}
	return r;
}

int n;
int a[3];
int nodes;
int suf[SUML];
bool vis[SUML];
vector<int> act;
int go[E][SUML];
int memo[N][SUML];
vector< vector<int> > pat[3];

void insert(vector<int> &v){
	int pos = 0;
	for(int i = 0; i < v.size(); i++){
		int nxt = v[i];
		if(go[nxt][pos] == 0){
			go[nxt][pos] = nodes++;
		}
		pos = go[nxt][pos];
	}
	vis[pos] = true;
}

void backtracking(int id, int val){
	if(val == 0){
		pat[id].emplace_back(act);
		return;
	}
	for(int i = 0; i < E; i++){
		if(i + 1 > val) break;
		act.emplace_back(i);
		backtracking(id, val - i - 1);
		act.pop_back();
	}
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		if(vis[suf[u]]) vis[u] = true;
		for(int i = 0; i < E; i++){
			if(go[i][u]){
				int v = go[i][u];
				suf[v] = u == 0 ? 0 : go[i][suf[u]];
				Q.emplace(v);
			}
			else{
				go[i][u] = u == 0 ? 0 : go[i][suf[u]];
			}
		}
	}
}

void preprocess(){
	for(int i = 0; i < 3; i++){
		backtracking(i, a[i]);
	}
	nodes = 1;
	for(vector<int> x : pat[0]){
		for(vector<int> y : pat[1]){
			for(vector<int> z : pat[2]){
				vector<int> cur = x;
				for(auto w : y) cur.emplace_back(w);
				for(auto w : z) cur.emplace_back(w);
				insert(cur);
			}
		}
	}
	BFS(0);
}

int solve(){
	memo[0][0] = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < nodes; j++){
			for(int c = 0; c < E; c++){
				if(vis[go[c][j]]) continue;
				memo[i + 1][go[c][j]] += memo[i][j];
				if(memo[i + 1][go[c][j]] >= MOD) memo[i + 1][go[c][j]] -= MOD;
			}
		}
	}
	int ans = pow_mod(10, n);
	for(int i = 0; i < nodes; i++){
		ans += MOD - memo[n][i];
		if(ans >= MOD) ans -= MOD;
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < 3; i++) scanf("%d", a + i);
	preprocess();
	printf("%d\n", solve());
	return 0;
}
