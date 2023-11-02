#include<bits/stdc++.h>
using namespace::std;

const int E = 26;

struct AhoCorasick {
	vector<int> suf;
	vector<int> mask;
	vector<vector<int>> go;
	AhoCorasick(vector<string> words) {
		add_node();
		for(int i = 0; i < words.size(); i++) {
			insert(words[i], i);
		}
		BFS(0);
	}

	void add_node() {
		suf.emplace_back(0);
		mask.emplace_back(0);
		go.emplace_back(vector<int>(E, 0));
	}

	void insert(string s, int id) {
		int pos = 0;
		for(int i = 0; i < s.size(); i++) {
			int c = s[i] - 'A';
			if(go[pos][c] == 0) {
				go[pos][c] = suf.size();
				add_node();
			}
			pos = go[pos][c];
		}
		mask[pos] |= 1 << id;
	}

	void BFS(int src) {
		queue<int> Q;
		Q.emplace(src);
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			mask[u] |= mask[suf[u]];
			for(int c = 0; c < E; c++) {
				if(go[u][c]) {
					int v = go[u][c];
					suf[v] = u == 0 ? 0 : go[suf[u]][c];
					Q.emplace(v);
				}
				else { 
					go[u][c] = u == 0 ? 0 : go[suf[u]][c];
				}
			}
		}
	}

	int g(int u, int c) {
		return go[u][c];
	}

	int get_mask(int u) {
		return mask[u];
	}

	int get_nodes() {
		return suf.size();
	}

};

class JoinedString {
public:
	
	string joinWords(vector<string> words) {
		AhoCorasick A(words);
		const int M = 1 << words.size();
		const int N = A.get_nodes();
		vector<vector<int>> D(N, vector<int>(M, -1));
		vector<vector<pair<int, int>>> P(N, vector<pair<int, int>>(M));
		vector<vector<int>> in(N, vector<int>(M, -1));
		vector<vector<int>> C(N, vector<int>(M, -1));
		D[0][0] = 0;
		queue<pair<int, int>> Q;
		Q.emplace(0, 0);
		int T = 0;
		while(!Q.empty()) {
			int state, mask;
			tie(state, mask) = Q.front(); Q.pop();
			in[state][mask] = T++;
			for(int c = 0; c < E; c++) {
				int nstate = A.g(state, c);
				int nmask = mask | A.get_mask(nstate);
				if(~D[nstate][nmask]) continue;
				D[nstate][nmask] = D[state][mask] + 1;
				C[nstate][nmask] = c;
				P[nstate][nmask] = make_pair(state, mask);
				Q.emplace(nstate, nmask);
			}
		}
		int best = INT_MAX;
		int start = -1;
		int wanted_mask = M - 1;
		for(int i = 0; i < N; i++) {
			if(D[i][wanted_mask] == -1) continue;
			if(D[i][wanted_mask] < best) {
				start = i;
				best = D[i][wanted_mask];
			}
			else if(D[i][wanted_mask] == best and in[i][wanted_mask] < in[start][wanted_mask]) {
				start = i;
			}
		}
		string res = "";
		while(start or wanted_mask) {
			res.push_back('A' + C[start][wanted_mask]);
			tie(start, wanted_mask) = P[start][wanted_mask];
		}
		reverse(res.begin(), res.end());
		return res;
	}
};
