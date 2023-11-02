#include<iostream>
#include<cstdio>
#include<cstring>
using namespace::std;

const int N = 10000 + 5;

int n;
int pi[N];
char s[N];

void prefix(){
	int k = 0;
	for(int i = 1; i < n; i++){
		while(k > 0 and s[k] != s[i]) k = pi[k - 1];
		if(s[k] == s[i]) k += 1;
		pi[i] = k;
	}
}

int solve(){
	prefix();
	getchar();
	int k = 0;
	int ans = 0;
	char c = getchar();
	while(c != '\n'){
		while(k > 0 and s[k] != c) k = pi[k - 1];
		if(s[k] == c) k += 1;
		if(k == n) ans += 1;
		c = getchar();
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s", s);
		n = strlen(s);
		printf("%d\n", solve());
	}
	return 0;
}
