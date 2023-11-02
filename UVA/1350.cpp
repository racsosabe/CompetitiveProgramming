#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

bool vis[N][2];
int memo[N][2];
vector<int> cnt;

void init() {
	cnt.emplace_back(0);
	cnt.emplace_back(1);
	cnt.emplace_back(1);
	int sum = 2;
	while(sum < 90000000) {
		cnt.emplace_back(cnt.back() + cnt[cnt.size() - 2]);
		sum += cnt.back();
	}
}

int DP(int len, int last) {
	if(len == 0) return 1;
	if(vis[len][last]) return memo[len][last];
	int res = DP(len - 1, 0);
	if(!last) res += DP(len - 1, 1);
	vis[len][last] = true;
	return memo[len][last] = res;
}

void DFS(int len, int last, int k) {
	if(len == 0) {
		puts("");
		return;
	}
	if(DP(len - 1, 0) >= k) {
		putchar('0');
		DFS(len - 1, 0, k);
	}
	else {
		putchar('1');
		DFS(len - 1, 1, k - DP(len - 1, 0));
	}
}

void print_kth(int n) {
	int len = 0;
	while(n > cnt[len]) {
		n -= cnt[len];
		len += 1;
	}
	int total = DP(len - 1, 1);
	putchar('1');
	DFS(len - 1, 1, n);
}

int main() {
	init();
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		print_kth(n);
	}
	return 0;
}
