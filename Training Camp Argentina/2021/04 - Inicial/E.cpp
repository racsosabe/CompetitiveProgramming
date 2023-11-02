#include<bits/stdc++.h>
using namespace::std;

const int MAX = 2000000 + 5;

int n;
int L[MAX];
int cnt[MAX];

int solve(){
	for(int i = 1; i < MAX; i++){
		if(cnt[i]) L[i] = i;
		else L[i] = L[i - 1];
	}
	int ans = 0;
	for(int i = 2; i < MAX; i++){
		if(cnt[i]){
			for(int j = i; j + i - 1 < MAX; j += i){
				if(L[j + i - 1] >= j) ans = max(ans, L[j + i - 1] % i);
			}
		}
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		cnt[x] = 1;
	}
	printf("%d\n", solve());
	return 0;
}
