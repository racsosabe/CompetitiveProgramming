#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int a[N];
stack<int> S;

long long solve(){
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		while(!S.empty() and a[S.top()] >= a[i]){
			int cur = S.top(); S.pop();
			ans = max(ans, 1ll * a[cur] * (i - 1 - (S.empty() ? 0 : S.top())));
		}
		S.push(i);
	}
	while(!S.empty()){
		int cur = S.top(); S.pop();
		ans = max(ans, 1ll * a[cur] * (n - (S.empty() ? 0 : S.top())));
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%lld\n", solve());
	return 0;
}
