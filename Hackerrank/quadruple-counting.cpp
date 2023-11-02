#include<bits/stdc++.h>
using namespace::std;

const int N = 50000 + 5;
const int MAX = 1 << 8;
const int L = 8;

int n;
int a[N];
int b[N];
int c[N];
int v[N];
long long w[N];
long long new_w[N];
long long cnt[MAX][MAX][L + 1];

void update_1(int id, int x, long long add) {
	for(int mask = 0; mask < MAX; mask++) {
		int to = x & mask;
		cnt[id][mask][__builtin_popcount(to)] += add;
	}
}

void apply_1() {
	memset(cnt, 0, sizeof cnt);
	for(int i = 0; i < n; i++) {
		new_w[i] = 0;
		int id = a[i] / MAX, pr = a[i] & (MAX - 1);
		for(int mask = 0; mask < MAX; mask++) {
			int at = mask & id;
			if(__builtin_popcount(at) > v[i]) continue;
			int left = v[i] - __builtin_popcount(at);
			if(left <= L) new_w[i] += cnt[mask][pr][left];
		}
		update_1(id, pr, w[i]);
	}
}

void update_2(int id, int x, long long add) {
	for(int mask = 0; mask < MAX; mask++) {
		int to = x | mask;
		cnt[id][mask][__builtin_popcount(to)] += add;
	}
}

void apply_2() {
	memset(cnt, 0, sizeof cnt);
	for(int i = 0; i < n; i++) {
		new_w[i] = 0;
		int id = a[i] / MAX, pr = a[i] & (MAX - 1);
		for(int mask = 0; mask < MAX; mask++) {
			int at = mask | id;
			if(__builtin_popcount(at) > v[i]) continue;
			int left = v[i] - __builtin_popcount(at);
			if(left <= L) new_w[i] += cnt[mask][pr][left];
		}
		update_2(id, pr, w[i]);
	}
}


long long solve() {
	copy(b, b + n, v);
	fill(w, w + n, 1);
	apply_1();

	copy(c, c + n, v);
	copy(new_w, new_w + n, w);
	apply_2();

	copy(b, b + n, v);
	copy(new_w, new_w + n, w);
	apply_1();
	
	return accumulate(new_w, new_w + n, 0ll);
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++) scanf("%d", b + i);
	for(int i = 0; i < n; i++) scanf("%d", c + i);
	printf("%lld\n", solve());
	return 0;
}
