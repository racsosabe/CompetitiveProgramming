#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int n;

int main(){
	scanf("%d", &n);
	int ans = 1;
	for(int i = 1; i <= n; i++){
		int sum = 0;
		for(int j = 0; j < 6; j++){
			int x;
			scanf("%d", &x);
			sum += x;
		}
		ans = mul(ans, sum);
	}
	printf("%d\n", ans);
	return 0;
}
