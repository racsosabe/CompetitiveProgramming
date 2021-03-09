#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
char s[N];
int pi[N];

int main(){
	scanf("%s", s);
	n = strlen(s);
	int k = 0;
	for(int i = 1; i < n; i++){
		while(k > 0 and s[k] != s[i]) k = pi[k - 1];
		if(s[k] == s[i]) k += 1;
		pi[i] = k;
	}
	for(int i = 0; i < n; i++){
		printf("%d%c", pi[i], " \n"[i + 1 == n]);
	}
	return 0;
}
