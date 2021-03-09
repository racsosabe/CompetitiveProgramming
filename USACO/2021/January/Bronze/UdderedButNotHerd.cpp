#include<bits/stdc++.h>
using namespace::std;

const int N = 1000;
const int E = 26;

int n;
char s[N];
int order[E];
char alphabet[N];

int main(){
	scanf("%s", alphabet);
	scanf("%s", s);
	for(int i = 0; i < E; i++){
		order[alphabet[i] - 'a'] = i;
	}
	n = strlen(s);
	int ans = 1;
	for(int i = 1; i < n; i++){
		if(order[s[i] - 'a'] <= order[s[i - 1] - 'a']) ans += 1;
	}
	printf("%d\n", ans);
	return 0;
}
