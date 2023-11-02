#include<bits/stdc++.h>
using namespace::std;

const int SUML = 600000 + 5;
const int B[] = {311, 257};
const int MOD = 1e9 + 7;

int mul(long long a, long long b) {	
	return a * b % MOD;
}

int add(int a, int b) {
	return a + b < MOD ? a + b : a + b - MOD;
}

int n;
int q;
char s[SUML];
int pot[2][SUML];
set<pair<int, int>> H;

int id(char c) {
	return c - 'a' + 1;
}

void init() {
	for(int id = 0; id < 2; id++) {
		pot[id][0] = 1;
		for(int i = 1; i < SUML; i++) pot[id][i] = mul(B[id], pot[id][i - 1]);
	}
}

void insert() {
	int hsh1 = 0, hsh2 = 0;
	for(int i = 0; s[i]; i++) {
		hsh1 = add(hsh1, mul(pot[0][i], id(s[i])));
		hsh2 = add(hsh2, mul(pot[1][i], id(s[i])));
	}
	H.emplace(hsh1, hsh2);
}

bool solve() {
	int hsh1 = 0, hsh2 = 0;
	for(int i = 0; s[i]; i++) {
		hsh1 = add(hsh1, mul(pot[0][i], id(s[i])));
		hsh2 = add(hsh2, mul(pot[1][i], id(s[i])));
	}
	for(int i = 0; s[i]; i++) {
		int c = id(s[i]);
		for(int x = 1; x <= 3; x++) {
			if(x == c) continue;
			int new_hsh1 = add(hsh1, mul(pot[0][i], add(x, MOD - c)));
			int new_hsh2 = add(hsh2, mul(pot[1][i], add(x, MOD - c)));
			if(H.count(make_pair(new_hsh1, new_hsh2))) return true;
		}
	}
	return false;
}

int main() {
	init();
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) {
		scanf("%s", s);
		insert();
	}
	while(q--) {
		scanf("%s", s);
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
