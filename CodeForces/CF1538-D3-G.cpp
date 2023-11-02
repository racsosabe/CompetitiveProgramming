#include<bits/stdc++.h>
using namespace::std;

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int x, y, a, b;
		scanf("%d %d %d %d", &x, &y, &a, &b);
		if(a > b) swap(a, b);
		b -= a;
		if(b == 0){
			printf("%d\n", min(x, y) / a);
			continue;
		}
		int lo = 0, hi = x + y;
		while(lo < hi){
			int mi = lo + (hi - lo + 1) / 2;
			if(1ll * a * mi <= min(x, y) and (x - a * mi) / b + (y - a * mi) / b >= mi) lo = mi;
			else hi = mi - 1;
		}
		printf("%d\n", lo);
	}
	return 0;
}
