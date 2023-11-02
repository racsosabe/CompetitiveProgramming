#include<bits/stdc++.h>
using namespace::std;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int s, d;
		scanf("%d %d", &s, &d);
		if(s < 0 or d < 0 or s + d < 0 or s - d < 0 or (s + d) & 1) puts("impossible");
		else {
			int a = (s + d) / 2;
			int b = (s - d) / 2;
			printf("%d %d\n", a, b);
		}
	}
	return 0;
}
