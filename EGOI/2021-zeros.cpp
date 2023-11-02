#include<bits/stdc++.h>
using namespace::std;

long long a;
long long b;

int get(long long l, long long r, int val){
	long long pot = 1;
	int ans = 0;
	while(1.0 * pot * val <= r + 1e2){
		pot *= val;
		long long L = ((l + pot - 1) / pot) * pot;
		long long R = (r / pot) * pot;
		if(L <= R){
			ans += 1;
		}
		else break;
	}
	return ans;
}

int main(){
	scanf("%lld %lld", &a, &b);
	printf("%d\n", min(get(a, b, 2), get(a, b, 5)));
	return 0;
}
