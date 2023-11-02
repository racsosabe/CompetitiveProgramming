#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int a[N];
int ans[N];

void solve(){
	stack<int> S;
	for(int i = 1; i <= n; i++){
		while(!S.empty() and a[S.top()] >= a[i]){
			int cur = S.top(); S.pop();
			int len = i - 1 - (S.empty() ? 0 : S.top());
			ans[len] = max(ans[len], a[cur]);
		}
		S.emplace(i);
	}
	while(!S.empty()){
		int cur = S.top(); S.pop();
		int lst = S.empty() ? 0 : S.top();
		ans[n - lst] = max(ans[n - lst], a[cur]);
	}
	for(int i = n - 1; i >= 1; i--) ans[i] = max(ans[i], ans[i + 1]);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	solve();
	for(int i = 1; i <= n; i++){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
