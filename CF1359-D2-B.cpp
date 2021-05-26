#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int m;
int x;
int y;
char s[N];

int process(){
	int res = 0;
	int l = 0, r = 0;
	while(l < m){
		while(l < m and s[l] == '*') l++;
		if(l == m) break;
		r = l;
		while(r < m and s[r] == '.') r++;
		int len = r - l;
		res += min(len * x, (len / 2) * y + x * (len % 2));
		l = r;
	}
	return res;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d %d", &n, &m, &x, &y);
		int ans = 0;
		for(int i = 0; i < n; i++){
			scanf("%s", s);
			ans += process();
		}
		printf("%d\n", ans);
	}
	return 0;
}
