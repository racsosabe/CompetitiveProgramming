#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;
const int M = 4000 + 5;
const long long inf = 1e18;

int n;
int m;
int len;
int d[N];
int c[N];
int s[N];
int par[N][M];
pair<long long, int> ft[M][N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++) S.emplace(d[i]);
	map<int, int> id;
	for(auto x : S){
		id[x] = len++;
	}
	for(int i = 1; i <= n; i++) d[i] = id[d[i]];
}

void update(int id, int pos, long long val, int i){
	pos++;
	while(pos <= len){
		ft[id][pos] = min(ft[id][pos], make_pair(val, i));
		pos += (-pos) & pos;
	}
}

pair<long long, int> query(int id, int pos){
	pair<long long, int> res = {inf, -1};
	pos++;
	while(pos > 0){
		res = min(res, ft[id][pos]);
		pos &= pos - 1;
	}
	return res;
}

void solve(){
	compress();
	for(int i = 0; i < M; i++){
		for(int j = 0; j <= len; j++) ft[i][j] = {i == 0 ? 0 : inf, -1};
	}
	for(int i = 1; i <= n; i++){
		for(int j = M - 1; j >= s[i]; j--){
			pair<long long, int> res = query(j - s[i], len - 1 - d[i]);
			par[i][j] = res.second;
			if(res.first < inf) update(j, len - 1 - d[i], res.first + c[i], i);
		}
	}
	int best = m;
	pair<long long, int> act = query(best, len - 1);
	for(int i = m + 1; i < M; i++){
		pair<long long, int> cur = query(i, len - 1);
		if(cur.first < act.first){
			best = i;
			act = cur;
		}
	}
	if(act.first == inf){
		puts("-1");
		return;
	}
	stack<int> S;
	int start = act.second;
	int cur_s = best;
	while(start != -1){
		S.emplace(start);
		int nxt_start = par[start][cur_s];
		cur_s -= s[start];
		start = nxt_start;
	}
	printf("%lld %d\n", act.first, (int)S.size());
	while(!S.empty()){
		printf("%d", S.top());
		S.pop();
		putchar(" \n"[S.empty()]);
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d %d %d", d + i, s + i, c + i);
	}
	solve();
	return 0;
}
