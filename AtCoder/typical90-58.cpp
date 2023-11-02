#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int LOG = 63;

int n;
int s[N];
long long k;
int ST[N][LOG];

void init(){
	ST[0][0] = 0;
	for(int i = 1; i < N; i++){
		s[i] = i % 10 + s[i / 10];
		ST[i][0] = (i + s[i]) % 100000;
	}
	for(int d = 1; d < LOG; d++){
		for(int i = 0; i < N; i++){
			ST[i][d] = ST[ST[i][d - 1]][d - 1];
		}
	}
}

int main(){
	init();
	scanf("%d %lld", &n, &k);
	for(int i = 0; i < LOG; i++){
		if(k & (1LL << i)) n = ST[n][i];
	}
	printf("%d\n", n);
	return 0;
}
