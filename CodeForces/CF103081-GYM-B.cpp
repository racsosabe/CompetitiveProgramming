#include<bits/stdc++.h>
using namespace::std;

int main(){
	int n;
	scanf("%d", &n);
	int ans = INT_MAX;
	for(int i = 1; i <= n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		ans = min(ans, b / a);
	}
	printf("%d\n", ans);
	return 0;
}
