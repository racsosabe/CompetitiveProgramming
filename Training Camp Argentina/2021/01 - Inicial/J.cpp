#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const int M = 10000 + 5;

int n;
int m;
int L[N];
int a[N][N];
int memo[M];

void process(int id){
	int len;
	scanf("%d", &len);
	L[id] = len;
	vector<int> v(len);
	for(int i = 0; i < len; i++) scanf("%d", &v[i]);
	vector<int> prefix(v.begin(), v.end());
	for(int i = 1; i < len; i++) prefix[i] += prefix[i - 1];
	vector<int> suffix(v.begin(), v.end());
	for(int i = len - 2; i >= 0; i--) suffix[i] += suffix[i + 1];
	for(int i = 1; i <= len; i++){
		for(int j = 0; j <= i; j++){
			int sum = (j ? prefix[j - 1] : 0) + (i - j ? suffix[len - i + j] : 0);
			a[id][i] = max(a[id][i], sum);
		}
	}
}

int solve(){
	int total = 0;
	for(int i = 1; i <= n; i++){
		total += L[i];
		for(int val = total; val >= 1; val--){
			for(int j = 1, limit = min(val, L[i]); j <= limit; j++){
				memo[val] = max(memo[val], memo[val - j] + a[i][j]);
			}
		}
	}
	return memo[m];
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) process(i);
	printf("%d\n", solve());
	return 0;
}
