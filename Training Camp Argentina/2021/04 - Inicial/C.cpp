#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];
int cnt[3];
int prefix[3][N];
vector<pair<int, int>> res;

void init(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= 2; j++) prefix[j][i] = prefix[j][i - 1];
		prefix[a[i]][i] += 1;
	}
}

void check(int t){
	int L = 1;
	vector<int> sets(3, 0);
	bool correct = false;
	while(L <= n){
		int lo = L, hi = n;
		while(lo < hi){
			int mi = lo + (hi - lo) / 2;
			if(max(prefix[1][mi] - prefix[1][L - 1], prefix[2][mi] - prefix[2][L - 1]) < t) lo = mi + 1;
			else hi = mi;
		}
		if(prefix[1][lo] - prefix[1][L - 1] > prefix[2][lo] - prefix[2][L - 1]){
			sets[1] += 1;
		}
		else{
			sets[2] += 1;
		}
		if(max(prefix[1][lo] - prefix[1][L - 1], prefix[2][lo] - prefix[2][L - 1]) < t) return;
		if(lo == n) correct = true;
		L = lo + 1;
	}
	if(sets[a[n]] > sets[3 - a[n]] and correct){
		res.emplace_back(make_pair(sets[a[n]], t));
	}
}

void solve(){
	int win = a[n];
	int lose = 3 - a[n];
	vector<int> possible;
	for(int i = 1; i <= n; i++){
		check(i);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	init();
	solve();
	sort(res.begin(), res.end());
	printf("%d\n", (int)res.size());
	for(auto e : res) printf("%d %d\n", e.first, e.second);
	return 0;
}
