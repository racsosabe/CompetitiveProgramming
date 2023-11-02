#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
char s[N];
int d1[N];
int d2[N];

int solve(){
	int l = 0, r = -1;
	for(int i = 0; i < n; i++){
		d1[i] = max(1, min(r - i + 1, d1[l + r - i]));
		while(i >= d1[i] and i + d1[i] < n and s[i - d1[i]] != s[i + d1[i]]) d1[i] += 1;
		d1[i] -= 1;
		if(i + d1[i] > r){
			l = i - d1[i];
			r = i + d1[i];
		}
	}
	l = 0;
	r = -1;
	for(int i = 0; i < n; i++){
		d2[i] = max(0, min(r - i + 1, d2[l + r - i + 1]));
		while(i >= d2[i] and i + d2[i] < n and s[i - d2[i] - 1] != s[i + d2[i]]) d2[i] += 1;
		d2[i] -= 1;
		if(i + d2[i] > r){
			l = i - d2[i] - 1;
			r = i + d2[i];
		}
	}
	long long ans = 0;
	for(int i = 0; i < n; i++){
		ans += d2[i] + d1[i] + 1;
	}
	return ans > 100000 ? 100000 : ans;
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	printf("%d\n", solve());
	return 0;
}
