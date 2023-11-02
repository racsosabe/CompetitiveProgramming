#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int k;
int a[N];
int b[N];

int main(){
	scanf("%d %d", &n, &k);
	priority_queue<tuple<int, int, int>> Q;
	for(int i = 1; i <= n; i++){
		scanf("%d %d", a + i, b + i);
		Q.emplace(make_tuple(b[i], i, 0));
	}
	long long ans = 0;
	while(!Q.empty() and k > 0){
		int val, pos, type;
		tie(val, pos, type) = Q.top();
		Q.pop();
		ans += val;
		if(!type){
			Q.emplace(make_tuple(a[pos] - b[pos], pos, 1));
		}
		k -= 1;
	}
	printf("%lld\n", ans);
	return 0;
}
