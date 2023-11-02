#include<bits/stdc++.h>
using namespace::std;

const int MAX = 46;

int n;

vector<int> read(){
	vector<int> res(MAX, 0);
	for(int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		res[x % MAX] += 1;
	}
	return res;
}

int main(){
	scanf("%d", &n);
	vector<int> A = read();
	vector<int> B = read();
	vector<int> C = read();
	long long ans = 0;
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			int cur = (i + j) % MAX;
			int k = cur == 0 ? 0 : MAX - cur;
			ans += 1ll * A[i] * B[j] * C[k];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
