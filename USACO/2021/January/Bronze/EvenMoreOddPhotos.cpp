#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
	scanf("%d", &n);
	int cnt0 = 0, cnt1 = 0;
	for(int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		if(x & 1) cnt1 += 1;
		else cnt0 += 1;
	}
	int ans = 0;
	while(true){
		if(ans & 1){
			if(cnt1 > 0){
				ans += 1;
				cnt1 -= 1;
			}
			else break;
		}
		else{
			if(cnt0 > 0){
				ans += 1;
				cnt0 -= 1;
			}
			else if(cnt1 > 1){
				ans += 1;
				cnt1 -= 2;
			}
			else break;
		}
	}
	if(cnt1 > 0) ans -= 1;
	printf("%d\n", ans);
	return 0;
}
