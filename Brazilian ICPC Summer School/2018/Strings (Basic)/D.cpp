#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int z[N];
char s[N];

int main(){
	scanf("%s", s);
	n = strlen(s);
	int l = 0, r = 0;
	for(int i = 1; i < n; i++){
		z[i] = min(z[i - l], r - i + 1);
		if(z[i] < 0) z[i] = 0;
		while(i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i] += 1;
		if(r < i + z[i] - 1){
			l = i;
			r = i + z[i] - 1;
		}
	}
	for(int i = 0; i < n; i++){
		printf("%d%c", z[i], " \n"[i + 1 == n]);
	}
	return 0;
}
