#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int m;
int len;
int a[N];
bool vis[N];

bool backtracking(int pos, int sum, int last){
	if(pos == m){
		return true;
	}
	if(sum == len) return backtracking(pos + 1, 0, pos + 1);
	int last_failed = -1;
	for(int i = last; i < n; i++){
		if(vis[i]) continue;
		if(sum + a[i] > len) continue;
		if(a[i] == last_failed) continue;
		vis[i] = true;
		if(backtracking(pos, sum + a[i], i + 1)) return true;
		last_failed = a[i];
		vis[i] = false;
		if(sum == 0 or sum + a[i] == len) return false;
	}
	return false;
}

int main(){
	while(scanf("%d", &n) == 1 and n){
		assert(n <= 64); // n <= 64
		for(int i = 0; i < n; i++) scanf("%d", a + i);
		int L = accumulate(a, a + n, 0);
		sort(a, a + n, greater<int>());
		len = a[0];
		bool found = false;
		while(len <= L and !found){
			if(L % len == 0){
				for(int j = 0; j < n; j++) vis[j] = false;
				m = L / len;
				if(backtracking(0, 0, 0)){
					printf("%d\n", len);
					found = true;
				}
			}
			len += 1;
		}
	}
	return 0;
}
