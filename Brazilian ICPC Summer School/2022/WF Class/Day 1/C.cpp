#include<bits/stdc++.h>
using namespace::std;

const int C = ~(1 << 31);
const int M = (1 << 16) - 1;
const int N = 300000 + 5;

int n;
int m;
int a;
int b;
int len;
int memo[N];
set<pair<int, int>> ft[N];

int r(){
	a = 36969 * (a & M) + (a >> 16);
	b = 18000 * (b & M) + (b >> 16);
	return (C & ((a << 16) + b)) % 1000000;
}

void compress(vector<int> &v){
	vector<int> values(v.begin(), v.end());
	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
	for(int i = 0; i < v.size(); i++){
		v[i] = lower_bound(values.begin(), values.end(), v[i]) - values.begin();
	}
}

int get(int at, int val){
	if(ft[at].empty() or (*ft[at].begin()).first > val) return 0;
	set<pair<int, int>>::iterator it = ft[at].lower_bound(make_pair(val, -1));
	if(it == ft[at].end() or (*it).first > val) it--;
	return (*it).second;
}
	
int query(int y, int z){
	y++;
	int res = 0;
	for(int j = y; j > 0; j &= j - 1){
		res = max(res, get(j, z));
	}
	return res;
}

void insert(int at, int pos, int val){
	if(ft[at].empty()){
		ft[at].emplace(make_pair(pos, val));
		return;
	}
	set<pair<int, int>>::iterator it = ft[at].lower_bound(make_pair(pos, -1));

	if(it != ft[at].end() and (*it).first == pos and (*it).second >= val) return;
	set<pair<int, int>>::iterator leq = it;
	if(leq != ft[at].begin()) leq--;
	if((*leq).first < pos and (*leq).second >= val) return;
	vector<pair<int, int>> to_remove;
	while(it != ft[at].end() and (*it).second <= val){
		to_remove.emplace_back(*it);
		it++;
	}
	for(auto e : to_remove) ft[at].erase(e);
	ft[at].emplace(make_pair(pos, val));
}

void update(int y, int z, int val){
	y++;
	for(int j = y; j <= len; j += (-j) & j){
		insert(j, z, val);
	}
}

int solve(vector<int> &x, vector<int> &y, vector<int> &z){
	vector<int> p(len);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(x[i] != x[j]) return x[i] < x[j];
		if(y[i] != y[j]) return y[i] < y[j];
		if(z[i] != z[j]) return z[i] < z[j];
		return false;
	});
	int ans = 0;
	int l = 0, r = 0;
	while(l < len){
		while(r < len and x[p[l]] == x[p[r]]) r++;
		for(int i = l; i < r; i++){
			int at = p[i];
			memo[i] = 1 + query(y[at] - 1, z[at] - 1);
			if(ans < memo[i]) ans = memo[i];
		}
		for(int i = l; i < r; i++){
			int at = p[i];
			update(y[at], z[at], memo[i]);
		}
		l = r;
	}
	return ans;
}

void clear(){
	for(int i = 0; i <= len; i++){
		ft[i].clear();
	}
}

int main(){
	while(scanf("%d %d %d %d", &m, &n, &a, &b) == 4 and m + n){
		len = n + m;
		vector<int> x(len), y(len), z(len);
		for(int i = 0; i < m; i++){
			scanf("%d %d %d", &x[i], &y[i], &z[i]);
		}
		for(int i = m; i < len; i++){
			x[i] = r();
			y[i] = r();
			z[i] = r();
		}
		compress(x); compress(y); compress(z);
		printf("%d\n", solve(x, y, z));
		clear();
	}
	return 0;
}
