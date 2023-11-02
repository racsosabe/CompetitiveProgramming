#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
char s[N];

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		vector<int> cnt(26, 0);
		for(int i = 1; i <= n; i++){
			scanf("%s", s);
			for(int j = 0; s[j]; j++) cnt[s[j] - 'a'] += 1;
		}
		bool can = true;
		for(auto x : cnt) if(x % n) can = false;
		puts(can ? "YES" : "NO");
	}
	return 0;
}
