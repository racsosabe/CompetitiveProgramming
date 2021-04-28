#include<bits/stdc++.h>
using namespace::std;

const int limit = 9999;

int a, b, c, n;

int main(){
	scanf("%d %d %d %d", &n, &a, &b, &c);
	int ans = limit;
	for(int i = 0; i <= ans and a * i <= n; i++){
		for(int j = 0; i + j <= ans and a * i + b * j <= n; j++){
			int left = n - a * i - b * j;
			if(left % c) continue;
			ans = min(ans, i + j + left / c);
		}
	}
	printf("%d\n", ans);
	return 0;
}
