#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int inf = 2e9 + 10;

int n;
int q;
int x[N];
int y[N];
int valX[N];
int valY[N];
long long ans[N];
long long st[4 * N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++){
		S.emplace(x[i]);
	}
	int len = 0;
	map<int, int> id;
	for(int a : S){
		valX[len] = a;
		id[a] = len++;
	}
	for(int i = 1; i <= n; i++) x[i] = id[x[i]];
	S.clear();
	for(int i = 1; i <= n; i++){
		S.emplace(y[i]);
	}
	len = 0;
	id.clear();
	for(int a : S){
		valY[len] = a;
		id[a] = len++;
	}
	for(int i = 1; i <= n; i++) y[i] = id[y[i]];
}

void build(int pos = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] = -inf;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = -inf;
}

void update(int x, long long y, int pos = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] = max(st[pos], y);
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = max(st[2 * pos], st[2 * pos + 1]);
}

long long query(int x, int y, int pos = 1, int l = 0, int r = n - 1){
	if(y < l or r < x or x > y) return -inf;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return max(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1 , r));
}

void preprocess(){
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(y[i] == y[j]) return x[i] < x[j];
		return y[i] > y[j];
	});
	build();
	for(int i : p){
		long long best_here = valX[x[i]] - valY[y[i]] + query(0, x[i]);
		ans[i] = max(ans[i], best_here);
		update(x[i], -valX[x[i]] + valY[y[i]]);
	}
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(y[i] == y[j]) return x[i] > x[j];
		return y[i] < y[j];
	});
	build();
	for(int i : p){
		long long best_here = - valX[x[i]] + valY[y[i]] + query(x[i], n - 1);
		ans[i] = max(ans[i], best_here);
		update(x[i], valX[x[i]] - valY[y[i]]);
	}
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(y[i] == y[j]) return x[i] > x[j];
		return y[i] > y[j];
	});
	build();
	for(int i : p){
		long long best_here = -valX[x[i]] - valY[y[i]] + query(x[i], n - 1);
		ans[i] = max(ans[i], best_here);
		update(x[i], valX[x[i]] + valY[y[i]]);
	}
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(y[i] == y[j]) return x[i] < x[j];
		return y[i] < y[j];
	});
	build();
	for(int i : p){
		long long best_here = valX[x[i]] + valY[y[i]] + query(0, x[i]);
		ans[i] = max(ans[i], best_here);
		update(x[i], - valX[x[i]] - valY[y[i]]);
	}
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d %d", x + i, y + i);
	compress();
	preprocess();
	for(int i = 1; i <= q; i++){
		int p;
		scanf("%d", &p);
		printf("%lld\n", ans[p]);
	}
	return 0;
}
