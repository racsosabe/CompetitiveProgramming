#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int q;
int h[N];
int T = 0;
int in[N];
int out[N];
int nxt[N];
int par[N];
int subtree[N];
vector<int> G[N];
long long st[4 * N];
long long lazya[4 * N];
long long lazyr[4 * N];


void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p){
			swap(G[u].back(), G[u][i]);
		}
		int v = G[u][i];
		if(v == p) continue;
		DFS(v, u);
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][i], G[u][0]);
		}
		subtree[u] += subtree[v];
	}
	if(p != -1){
		G[u].pop_back();
	}
}

void HLD(int u){
	in[u] = T++;
	cerr << u << " ";
	for(int v : G[u]){
		par[v] = u;
		nxt[v] = (v == G[u][0] ? nxt[u] : v);
		h[v] = h[u] + 1;
		HLD(v);
	}
	out[u] = T - 1;
}

void push(int pos, int l, int r){
	if(lazya[pos] or lazyr[pos]){
		int len = r - l;
		st[pos] += lazyr[pos] * len * (len + 1) / 2 + (r - l + 1) * lazya[pos];
		int mi = (l + r) / 2;
		if(l < r){
			lazyr[2 * pos] += lazyr[pos];
			lazyr[2 * pos + 1] += lazyr[pos];
			lazya[2 * pos] += lazya[pos];
			lazya[2 * pos + 1] += lazya[pos] + (mi - l + 1) * lazyr[pos];
		}
		lazya[pos] = lazyr[pos] = 0;
	}
}

void update(int x, int y, int z, int R, int pos = 1, int l = 0, int r = n - 1){
	push(pos, l, r);
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y){
		lazya[pos] += z;
		lazyr[pos] += R;
		push(pos, l, r);
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, z, R, 2 * pos, l, mi);
	update(x, y, z + R * max(0, (mi - max(l, x) + 1)), R, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

long long query(int x, int y, int pos = 1, int l = 0, int r = n - 1){
	push(pos, l, r);
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int lca(int u, int v){
	while(nxt[u] != nxt[v]){
		if(h[nxt[u]] < h[nxt[v]]) swap(u, v);
		u = par[nxt[u]];
	}
	if(h[u] > h[v]) swap(u, v);
	return u;
}

void upload(vector< pair<int, int> > &v, int len, int k){
	bool take = false;
	int cur = 1;
	for(auto x : v){
		int l = x.first;
		int r = x.second;
		int L = r - l + 1;
		if(take){
			update(l, r, cur - (L - 1), 1);
			cur -= L;
		}
		else{
			if(cur + L - 1 <= k){
				update(l, r, cur + L - 1, -1);
				cur += L;
				if(cur == k + 1){
					cur = len & 1 ? k - 1 : k;
					take = true;
				}
			}
			else{
				int p = k - cur + 1;
				update(r - p + 1, r, k, -1);
				cur = len & 1 ? k - 1 : k;
				update(l, r - p, cur - (r - l - p), 1);
				cur -= r - l - p + 1;
				take = true;
			}
		}
	}

}

void change(int u, int v){
	int x = lca(u, v);
	int len = h[u] + h[v] - 2 * h[x];
	vector< pair<int, int> > Iu, Iv;
	while(nxt[u] != nxt[v]){
		if(h[nxt[u]] > h[nxt[v]]){
			Iu.emplace_back(make_pair(in[nxt[u]], in[u]));
			u = par[nxt[u]];
		}
		else{
			Iv.emplace_back(make_pair(in[nxt[v]], in[v]));
			v = par[nxt[v]];
			
		}
	}
	if(h[u] > h[v]){
		Iu.emplace_back(make_pair(in[v] + 1, in[u]));
	}
	else{
		Iv.emplace_back(make_pair(in[u] + 1, in[v]));
	}
	int k = (len + 1) / 2;
	upload(Iu, len, k);
	upload(Iv, len, k);
}

long long solve(int u, int v){
	long long ans = 0;
	while(nxt[u] != nxt[v]){
		if(h[nxt[u]] < h[nxt[v]]) swap(u, v);
		ans += query(in[nxt[u]], in[u]);
		u = par[nxt[u]];
	}
	if(h[u] > h[v]) swap(u, v);
	ans += query(in[u] + 1, in[v]);
	return ans;
}

int main(){
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(1);
	HLD(1);
	cerr << endl;
	q += m;
	for(int i = 0; i < q; i++){
		int op, u, v;
		scanf("%d %d %d", &op, &u, &v);
		if(op == 1){
			change(u, v);
		}
		else{
			printf("%lld\n", solve(u, v));
		}
	}
	return 0;
}
