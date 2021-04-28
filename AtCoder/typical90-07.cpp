#include<bits/stdc++.h>
using namespace::std;

int n;
int q;
set<int> S;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		S.emplace(x);
	}
	scanf("%d", &q);
	while(q--){
		int x;
		scanf("%d", &x);
		set<int>::iterator it = S.lower_bound(x);
		int ans = INT_MAX;
		if(it != S.end()){
			ans = min(ans, *it - x);
		}
		if(it != S.begin()){
			it--;
			ans = min(ans, x - *it);
		}
		printf("%d\n", ans);
	}
	return 0;
}
