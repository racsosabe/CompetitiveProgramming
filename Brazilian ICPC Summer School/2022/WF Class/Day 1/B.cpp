#include<bits/stdc++.h>
using namespace::std;

const int N = 40000 + 5;
const int SUML = 2 * N;
const int E = 26;

int n;
int m;
int last;
int nodes;
char s[N];
int pos[SUML];
int len[SUML];
int link[SUML];
int frec[SUML];
int nxt[SUML][E];
bool prefix[SUML];

void sa_extend(int c, int at){
	int cur = nodes++;
	len[cur] = len[last] + 1;
	pos[cur] = at;
	prefix[cur] = true;
	int p = last;
	while(~p and !nxt[p][c]){
		nxt[p][c] = cur;
		p = link[p];
	}
	if(p == -1){
		link[cur] = 0;
	}
	else{
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]){
			link[cur] = q;
		}
		else{
			int clone = nodes++;
			len[clone] = len[p] + 1;
			link[clone] = link[q];
			for(int j = 0; j < E; j++) nxt[clone][j] = nxt[q][j];
			pos[clone] = pos[q];
			prefix[clone] = false;
			while(~p and nxt[p][c] == q){
				nxt[p][c] = clone;
				p = link[p];
			}
			link[q] = link[cur] = clone;
		}
	}
	last = cur;
}

void clear(){
	for(int i = 0; i < nodes; i++){
		memset(nxt[i], 0, sizeof nxt[i]);
		link[i] = -1;
		frec[i] = 0;
		prefix[i] = false;
	}
}

void propagate(){
	vector<int> p(nodes);
	vector<int> head(n + 1, 0);
	for(int i = 0; i < nodes; i++) head[len[i]]++;
	int sum = 0;
	for(int i = 0; i <= n; i++){
		sum += head[i];
		head[i] = sum - head[i];
	}
	for(int i = 0; i < nodes; i++){
		p[head[len[i]]++] = i;
	}
	reverse(p.begin(), p.end());
	for(auto x : p){
		frec[x] += prefix[x];
		if(~link[x]){
			frec[link[x]] += frec[x];
			pos[link[x]] = max(pos[link[x]], pos[x]);
		}
	}
}

void solve(){
	int best_len = -1, best_pos = -1;
	for(int u = 0; u < nodes; u++){
		if(frec[u] >= m){
			if(best_len < len[u] or (best_len == len[u] and best_pos < pos[u])){
				best_len = len[u];
				best_pos = pos[u];
			}
		}
	}
	if(best_len > 0){
		printf("%d %d\n", best_len, best_pos - best_len + 1);
		return;
	}
	puts("none");
}

int main(){
	while(scanf("%d", &m) == 1 and m > 0){
		scanf("%s", s);
		n = strlen(s);
		link[0] = -1;
		last = 0;
		nodes = 1;
		for(int i = 0; s[i]; i++){
			sa_extend(s[i] - 'a', i);
		}
		propagate();
		solve();
		clear();
	}
	return 0;
}
