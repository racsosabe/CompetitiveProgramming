#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;

int main(){
	scanf("%d", &n);
	stack<int> S;
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		while(!S.empty() and S.top() <= x) S.pop();
		S.emplace(x);
	}
	printf("%d\n", (int)S.size());
	return 0;
}
