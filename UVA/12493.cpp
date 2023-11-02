#include<bits/stdc++.h>
using namespace::std;

int phi(int x){
	int ans = x;
	for(int i = 2; 1ll * i * i <= x; i++){
		if(x % i == 0){
			while(x % i == 0) x /= i;
			ans -= ans / i;
		}
	}
	if(x > 1) ans -= ans / x;
	return ans;
}

int main(){
	int n;
	while(scanf("%d", &n) == 1){
		int ans = phi(n);
		printf("%d\n", (ans + 1) / 2);
	}
	return 0;
}
