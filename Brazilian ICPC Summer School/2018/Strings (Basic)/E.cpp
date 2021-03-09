#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
char s[N];
int d1[N];
int d2[N];

int main(){
	scanf("%s", s);
	n = strlen(s);
	int l = 0, r = -1;
	for(int i = 0; i < n; i++){
		d1[i] = min(r - i + 1, d1[l + r - i]);
		if(d1[i] < 1) d1[i] = 1;
		while(i - d1[i] >= 0 and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]) d1[i] += 1;
		d1[i] -= 1;
		if(r < i + d1[i]){
			l = i - d1[i];
			r = i + d1[i];
		}
	}
	l = 0; r = -1;
	for(int i = 0; i < n; i++){
		d2[i] = min(r - i + 1, d2[l + r - i + 1]);
		if(d2[i] < 0) d2[i] = 0;
		while(i - d2[i] - 1 >= 0 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]) d2[i] += 1;
		d2[i] -= 1;
		if(r < i + d2[i]){
			l = i - d2[i] - 1;
			r = i + d2[i];
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++){
		int l = i - d1[i];
		if(l == 0) ans = max(ans, 2 * d1[i] + 1);
		if(d2[i] == -1) continue;
		l = i - d2[i] - 1;
		if(l == 0) ans = max(ans, 2 * (d2[i] + 1));
	}
	printf("%d\n", ans);
	return 0;
}
