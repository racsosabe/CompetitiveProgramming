#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
int n = 100;

int k;
int M[N][N];

int f(int x){
	return x * (x - 1) * (x - 2) / 6;
}

bool has(int pos){
	for(int i = 0; i < 100; i++) if(M[i][pos]) return true;
	return false;
}

void solve(){
	int len = 3;
	while(f(len + 1) <= k) len++;
	k -= f(len);
	for(int i = 0; i < len; i++){
		for(int j = i + 1; j < len; j++){
			M[i][j] = M[j][i] = 1;
		}
	}
	for(int i = len; i < 100; i++){
		int best = 0;
		while(best * (best + 1) / 2 <= k and best + 1 <= len) best++;
		if(best <= 1) break;
		k -= best * (best - 1) / 2;
		for(int j = 0; j < best; j++){
			M[i][j] = M[j][i] = 1;
		}
	}
	n = len;
	while(has(n)) n += 1;
}

int main(){
	scanf("%d", &k);
	solve();
	printf("%d\n", n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			putchar('0' + M[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
