#include<bits/stdc++.h>
using namespace::std;

const int N = 50000 + 5;

int n;
int x[N];
int y[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &x[i], &y[i]);
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		int j = i + 1 <= n ? i + 1 : 1;
		ans += x[i] * y[j] - x[j] * y[i];
	}
	printf("%lld.%lld\n", ans / 2, (ans & 1) * 5);
	return 0;
}
