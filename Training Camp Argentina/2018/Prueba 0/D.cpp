#include<bits/stdc++.h>
using namespace::std;

// 6 4 (0 4 6 0] -> l = 3, r = 6 -> [4, 6]
const int N = 1000000 + 5;

int n;
int L;
int a[N];

void solve(){
	int r = n;
	int ans = 0;
	stack<int> primeros_movimientos;
	while(r >= 1){
		int l = r;
		int sum = 0;
		while(r >= 1 and a[r] == 0) r -= 1;
		if(r < 1) break;
		while(l >= 1 and sum + a[l] <= L){
			sum += a[l];
			l -= 1;
			if(sum == L) break;
		}
		// (l, r]
		// l + 1, l + 2, ..., n -> n - l movimientos
		if(sum > 0){
			primeros_movimientos.emplace(l + 1);
			ans += n - l;
		}
		r = l;
	}
	printf("%d\n", ans);
	while(!primeros_movimientos.empty()){
		printf("%d", primeros_movimientos.top());
		primeros_movimientos.pop();
		putchar(" \n"[primeros_movimientos.empty()]);
	}
}

int main(){
	scanf("%d", &L);
	scanf("%d", &n);
	a[0] = L + 1;
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	solve();
	return 0;
}
