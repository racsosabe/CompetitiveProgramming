#include<bits/stdc++.h>
using namespace::std;

const int T = 2 * 100000 + 18 * 200000 + 5;
const int N = 100000 + 5;

int n;
int d[N];
int x[N];
int L[T];
int R[T];
int st[T];
int nodes;
int root[N];
vector<int> moves[N];

void addNode(int val = 0){
	st[nodes] = val;
	L[nodes] = R[nodes] = -1;
	nodes += 1;
}

pair<int, bool> parse(){
	char c = getchar();
	if(c == '\n') return make_pair(0, false);
	while(c != '+' and c != '-') c = getchar();
	int sign = c == '-' ? -1 : 1;
	c = getchar();
	int val = 0;
	while(c != '\n' and c != ' '){
		val = (val << 1) + (val << 3) + c - '0';
		c = getchar();
	}
	val++;
	return make_pair(val * sign, c != '\n');
}

void build(int pos, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] = 0;
		return;
	}
	if(L[pos] == -1){
		L[pos] = nodes;
		addNode();
	}
	if(R[pos] == -1){
		R[pos] = nodes;
		addNode();
	}
	int mi = (l + r) / 2;
	build(L[pos], l, mi);
	build(R[pos], mi + 1, r);
	st[pos] = st[L[pos]] + st[R[pos]];
}

void update(int x, int y, int last, int pos, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] += y;
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi){
		R[pos] = R[last];
		L[pos] = nodes;
		addNode(st[L[last]]);
		update(x, y, L[last], L[pos], l, mi);
	}
	else{
		L[pos] = L[last];
		R[pos] = nodes;
		addNode(st[R[last]]);
		update(x, y, R[last], R[pos], mi + 1, r);
	}
	st[pos] = st[L[pos]] + st[R[pos]];
}

int query(int x, int y, int pos, int l = 0, int r = n - 1){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, L[pos], l, mi) + query(x, y, R[pos], mi + 1, r);
}

int solve(){
	int cnt = 0;
	addNode();
	build(0);
	for(int i = 1; i <= n; i++){
		int last_root = root[i - 1];
		for(auto a : moves[i]){
			int cur_root = nodes;
			addNode();
			if(a < 0) update(-a - 1, -1, last_root, cur_root);
			else update(a - 1, 1, last_root, cur_root);
			last_root = cur_root;
		}
		root[i] = last_root;
	}
	for(int i = 1; i <= n; i++){
		x[i] = (x[i - 1] + query(x[i - 1], n - 1, root[d[i]])) % n;
	}
	return x[n];
}

int main(){
	scanf("%d", &n);
	getchar();
	for(int i = 1; i <= n; i++){
		pair<int, bool> a;
		while(true){
			a = parse();
			if(a.first) moves[i].emplace_back(a.first);
			if(not a.second) break;
		}
	}
	for(int i = 1; i <= n; i++) scanf("%d", d + i);
	printf("%d\n", solve());
	return 0;
}
