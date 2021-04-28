#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int q;
int ac[3][N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= 2; j++) ac[j][i] = ac[j][i - 1];
		int c, p;
		scanf("%d %d", &c, &p);
		ac[c][i] += p;
	}
	scanf("%d", &q);
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d %d\n", ac[1][r] - ac[1][l - 1], ac[2][r] - ac[2][l - 1]);
	}
	return 0;
}
