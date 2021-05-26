#include<bits/stdc++.h>
using namespace::std;

const int N = 50 + 5;

int n;
int deg[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int x;
		scanf("%d", &x);
		deg[x]++;
		deg[i]++;
	}
	int ans = -1;
	for(int i = 0; i < n; i++){
		int c;
		scanf("%d", &c);
		if(deg[i] == 1) ans = max(ans, c);
	}
	printf("%d\n", ans);
	return 0;
}
