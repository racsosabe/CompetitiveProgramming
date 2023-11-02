#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;
const int LOG = 20;
const int inf = 1e9;

int n;
char s[N];
int pos[N];
int memo[N];
int st[4 * N];
int ST[N][LOG];

vector<int> suffix_array(){
	s[n++] = 0;
	vector<int> a(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];
	});
	vector<int> m(n);
	m[a[0]] = 0;
	for(int i = 1; i < n; i++){
		m[a[i]] = m[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}
	int len = 1;
	vector<int> nm(n);
	vector<int> sbs(n);
	vector<int> head(n);
	while(len < n){
		for(int i = 0; i < n; i++){
			sbs[i] = (a[i] - len + n) % n;
		}
		for(int i = n - 1; i >= 0; i--){
			head[m[a[i]]] = i;
		}
		for(int i = 0; i < n; i++){
			int x = sbs[i];
			a[head[m[x]]++] = x;
		}
		nm[a[0]] = 0;
		for(int i = 1; i < n; i++){
			if(m[a[i]] != m[a[i - 1]]){
				nm[a[i]] = nm[a[i - 1]] + 1;
			}
			else{
				int pre = m[(a[i - 1] + len) % n];
				int cur = m[(a[i] + len) % n];
				nm[a[i]] = nm[a[i - 1]] + (pre != cur);
			}
		}
		swap(m, nm);
		len <<= 1;
	}
	return a;
}

vector<int> lcp_array(vector<int> &a){
	vector<int> rank(n);
	for(int i = 0; i < n; i++){
		rank[a[i]] = i;
	}
	int k = 0;
	vector<int> lcp(n - 1);
	for(int i = 0; i < n; i++){
		if(rank[i] + 1 == n){
			k = 0;
			continue;
		}
		int j = a[rank[i] + 1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k += 1;
		lcp[rank[i]] = k;
		if(k > 0) k -= 1;
	}
	return lcp;
}

void buildST(vector<int> &v){
	for(int i = 0; i < v.size(); i++){
		ST[i][0] = v[i];
	}
	for(int d = 1; 1 << d <= v.size(); d++){
		int dis = 1 << (d - 1);
		for(int i = 0; i + 2 * dis - 1 < v.size(); i++){
			ST[i][d] = min(ST[i][d - 1], ST[i + dis][d - 1]);
		}
	}
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

void update(int x, int y, int pos = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] = y;
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = max(st[2 * pos], st[2 * pos + 1]);
}

int query(int x, int y, int pos = 1, int l = 0, int r = n - 1){
	if(y < l or r < x or x > y) return -inf;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return max(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

void preprocess(){
	vector<int> a = suffix_array();
	vector<int> lcp = lcp_array(a);
	for(int i = 0; i < a.size(); i++){
		pos[a[i]] = i;
	}
	buildST(lcp);
	build();
}

int getMin(int l, int r){
	r--;
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1 << k;
	return min(ST[l][k], ST[r - dis + 1][k]);
}

int solve(int i, int len){
	int lo = i, hi = n - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(getMin(i, mi) >= len) lo = mi;
		else hi = mi - 1;
	}
	int upper = lo;
	lo = 0; hi = i;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(getMin(mi, i) < len) lo = mi + 1;
		else hi = mi;
	}
	return query(lo, upper);
}

bool can(int i, int len){
	if(i + len < n) update(pos[i + len], memo[i + len]);
	return max(solve(pos[i], len - 1), solve(pos[i + 1], len - 1)) >= len - 1;
}

int solve(){
	int k = 0;
	int ans = 1;
	for(int i = n - 2; i >= 0; i--){
		k++;
		while(k > 1 and not can(i, k)) k -= 1;
		memo[i] = k;
		ans = max(ans, memo[i]);
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	preprocess();
	printf("%d\n", solve());
	return 0;
}
