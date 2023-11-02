#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int a[N];

int solve(){
	if(accumulate(a + 1, a + n + 1, 0ll) % n) return -1;
	int want = accumulate(a + 1, a + n + 1, 0ll) / n;
	int ans = n;
	for(int i = 1; i <= n; i++){
		if(a[i] <= want) ans -= 1;
	}
	return ans;
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
