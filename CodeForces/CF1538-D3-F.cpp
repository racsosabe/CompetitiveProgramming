#include<bits/stdc++.h>
using namespace::std;

int l;
int r;

int solve(){
	int ans = 0;
	while(r){
		ans += r - l;
		r /= 10;
		l /= 10;
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &l, &r);
		printf("%d\n", solve());
	}
	return 0;
}
