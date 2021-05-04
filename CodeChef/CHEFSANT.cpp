#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
long double ans[N];
vector< pair<int, int> > v;

void solve(){
	stack<int> S;
	for(int i = n - 1; i >= 0; i--){
		ans[i] = -1;
		while(!S.empty() and v[i].second <= v[S.top()].second) S.pop();
		while(!S.empty()){
			int nxt = S.top();
			ans[i] = 1.0 * (v[nxt].first - v[i].first) / (v[i].second - v[nxt].second);
			if(ans[nxt] != -1 and ans[i] > ans[nxt]) S.pop();
			else break;
		}
		S.push(i);
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		v.resize(n);
		for(int i = 0; i < n; i++){
			scanf("%d %d", &v[i].first, &v[i].second);
		}
		solve();
		for(int i = 0; i < n; i++){
			printf("%.10Lf%c", ans[i], " \n"[i + 1 == n]);
		}
	}
	return 0;
}
