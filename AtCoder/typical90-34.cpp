#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int k;
int a[N];
multiset<int> S;

int solve(){
	int r = 1;
	int ans = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		while(r <= n and cnt + (S.find(a[r]) == S.end()) <= k){
			if(S.find(a[r]) == S.end()) cnt++;
			S.emplace(a[r]);
			r += 1;
		}
		ans = max(ans, r - i);
		S.erase(S.find(a[i]));
		if(S.find(a[i]) == S.end()) cnt--;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%d\n", solve());
	return 0;
}
