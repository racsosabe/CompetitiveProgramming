#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int a[N];

int solve(){
	int l = min_element(a + 1, a + n + 1) - a;
	int r = max_element(a + 1, a + n + 1) - a;
	if(l > r) swap(l, r);
	return min({r, n - l + 1, l + n - r + 1});
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		printf("%d\n", solve());
	}
	return 0;
}
