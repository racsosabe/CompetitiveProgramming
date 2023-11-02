#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1e9 + 7;
const int N = 2000000 + 5;
const int E = 26;

int n;
int m;
int k;
int R[N];
char s[N];
int last[E];
int memo[N];

int solve() {
	memset(last, -1, sizeof last);
	memo[0] = 1;
	for(int i = 1; i <= n + m; i++) {
		int c = s[i - 1] - 'a';
		memo[i] = (memo[i - 1] + memo[i - 1]) % MOD;
		if(~last[c]) {
			memo[i] = (memo[i] + MOD - memo[last[c] - 1]) % MOD;
		}
		last[c] = i;
	}
	return memo[n + m];
}

int main() {
	scanf("%d %d", &n, &k);
	scanf("%s", s);
	m = strlen(s);
	memset(R, -1, sizeof R);
	for(int i = 0; i < m; i++) R[s[i] - 'a'] = i;
	vector<int> perm(k);
	iota(perm.begin(), perm.end(), 0);
	sort(perm.begin(), perm.end(), [&] (int i, int j){
		return R[i] < R[j];
	});
	for(int i = m; i < n + m; i++) s[i] = 'a' + perm[(i - m) % k];
	printf("%d\n", solve());
	return 0;
}
