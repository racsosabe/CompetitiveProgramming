#include<bits/stdc++.h>
using namespace::std;

const int N = 5000 + 5;
const int MOD = 1000000000 + 7;

int n;
int m;
char s[N];
int memo[N][N];

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	m = strlen(s);
	memo[0][0] = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= i; j++){
			memo[i + 1][j - 1]
		}
	}
	printf("%d\n", memo[n][m]);
	return 0;
}
