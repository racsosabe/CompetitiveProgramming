#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int a[N];
long long ac[N];

long long solve(){
	sort(a + 1, a + n + 1, greater<int>());
	for(int i = 1; i <= n; i++) ac[i] = a[i] + ac[i - 1];
	long long ans = ac[n];
	for(int i = 2; i <= n; i++) ans += ac[i];
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%lld\n", solve());
	return 0;
}
