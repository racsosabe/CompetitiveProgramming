#include<bits/stdc++.h>
using namespace::std;

const int N = 20000 + 5;
const int SUML = 300000 + 5;
const int E = 26;

int n;
int m;
int T;
int w[N];
int nodes;
string s[N];
int in[SUML];
int out[SUML];
int suf[SUML];
int sup[SUML];
int st[4 * N];
bool term[SUML];
int lazy[4 * N];
int go[SUML][E];
int edges;
int to[N];
int nxt[N];
int last[SUML];

void add_edge(int u, int v) {
	to[edges] = v;
	nxt[edges] = last[u];
	last[u] = edges++;
}

void insert(string &s) {
	int pos = 0;
	for(int i = 0; i < s.size(); i++) {
		int c = s[i] - 'a';
		if(go[pos][c] == 0) go[pos][c] = nodes++;
		pos = go[pos][c];
	}
	term[pos] = true;
}

void BFS(int src) {
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		sup[u] = term[suf[u]] ? suf[u] : sup[suf[u]];
		for(int c = 0; c < E; c++) {
			if(go[u][c]) {
				int v = go[u][c];
				Q.emplace(v);
				suf[v] = u == 0 ? 0 : go[suf[u]][c];
			}
			else {
				go[u][c] = u == 0 ? 0 : go[suf[u]][c];
			}
		}
	}
}

void build_aho() {
	nodes = 1;
	for(int i = 0; i < n; i++) {
		insert(s[i]);
	}
	BFS(0);
}

void DFS(int u) {
	in[u] = T++;
	for(int e = last[u]; ~e; e = nxt[e]) {
		DFS(to[e]);
	}
	out[u] = T - 1;
}

void build_graph() {
	edges = 0;
	for(int i = 1; i < nodes; i++) {
		if(not term[i]) continue;
		add_edge(sup[i], i);
	}
	T = 0;
	DFS(0);
}

void build(int pos = 1, int l = 0, int r = n) {
	lazy[pos] = 0;
	st[pos] = 0;
	if(l == r) return;
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
}

void push(int pos, int l, int r) {
	if(lazy[pos] > 0) {
		st[2 * pos] = max(st[2 * pos], lazy[pos]);
		st[2 * pos + 1] = max(st[2 * pos + 1], lazy[pos]);
		lazy[2 * pos] = max(lazy[2 * pos], lazy[pos]);
		lazy[2 * pos + 1] = max(lazy[2 * pos + 1], lazy[pos]);
		lazy[pos] = 0;
	}
}

void update(int x, int y, int z, int pos = 1, int l = 0, int r = n) {
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y) {
		st[pos] = max(st[pos], z);
		lazy[pos] = max(lazy[pos], z);
		return;
	}
	push(pos, l, r);
	int mi = (l + r) / 2;
	update(x, y, z, 2 * pos, l, mi);
	update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = max(st[2 * pos], st[2 * pos + 1]);
}

int query(int x, int pos = 1, int l = 0, int r = n) {
	if(l == r) return st[pos];
	push(pos, l, r);
	int mi = (l + r) / 2;
	if(x <= mi) return query(x, 2 * pos, l, mi);
	else return query(x, 2 * pos + 1, mi + 1, r);
}

void clear() {
	for(int i = 0; i < nodes; i++) {
		last[i] = -1;
		term[i] = false;
		memset(go[i], 0, sizeof go[i]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	memset(last, -1, sizeof last);
	while(t--) {
		cin >> n;
		m = 1;
		for(int i = 0; i < n; i++) {
			cin >> s[i] >> w[i];
			m += s[i].size();
		}
		build_aho();
		build_graph();
		build();
		int res = 0;
		for(int i = 0; i < n; i++) {
			int best = 0;
			int pos = 0;
			for(int j = 0; j < s[i].size(); j++) {
				int c = s[i][j] - 'a';
				pos = go[pos][c];
				int at = term[pos] ? in[pos] : in[sup[pos]];
				best = max(best, query(at));
			}
			best += w[i];
			res = max(res, best);
			if(best > 0) update(in[pos], out[pos], best);
		}
		cout << res << endl;
		if(t) clear();
	}
	return 0;
}
