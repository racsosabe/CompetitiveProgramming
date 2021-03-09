#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int z[N];
int pi[N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &pi[i]);
		if(pi[i] > 0) z[i - pi[i] + 1] = max(z[i - pi[i] - 1], pi[i]);
	}
	for(int i = 0; i < n; i++){
		printf("%d%c", z[i], " \n"[i + 1 == n]);
	}
	return 0;
}
