#include<bits/stdc++.h>
using namespace::std;

const int N = 20 + 5;

int n;
int a[N];
int h[N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++) scanf("%d", h + i);
	long long ans = 1;
	sort(a, a + n);
	sort(h, h + n);
	int pos = 0;
	for(int i = 0; i < n; i++){
		while(pos < n and h[pos] < a[i]) pos += 1;
		ans *= n - pos - (n - 1 - i);
	}
	printf("%lld\n", ans);
	return 0;
}
